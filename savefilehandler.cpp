#include "savefilehandler.h"

#include "cell.h"
#include "environment.h"

SaveFileHandler::SaveFileHandler(QObject *parent)
    : QObject{parent}
    , m_settings(QList<int>(3))
    , m_directory(QDir::current())
    , m_filename(QString("save.gol"))
{
}

SaveFileHandler::~SaveFileHandler()
{
}

void SaveFileHandler::setDirectory(QDir directory)
{
    m_directory = directory;

    return;
}

void SaveFileHandler::setFilename(QString filename)
{
    m_filename = filename;

    return;
}

void SaveFileHandler::clearBuffer()
{
    m_settings.fill(-1, 3);

    return;
}

bool SaveFileHandler::loadFromFile(Environment *environment)
{
    // Begin by clearing old buffer contents
    clearBuffer();

    // Build filepath and create QFile object
    QString fp = m_directory.absolutePath() + "/" + m_filename;
    QFile f(fp);

    // Check if file exists and can be opened
    if (!f.exists()) return false;
    if (!f.open(QIODevice::ReadOnly)) return false;

    // Create QTextStream object to handle file line by line
    QTextStream input(&f);

    // Create booleans to confirm writing of bufferSettings elements
    bool h = false;
    bool l = false;
    bool w = false;

    // Create boolean to track the start of data field characters
    bool ds = false;

    // Create QString to hold the lines
    QString line = QString();

    // Read loop for processing header of file
    while (!input.atEnd() && ds == false) {
        // Get the line
        line = input.readLine();

        // Get the first character to determine next step
        QChar firstChar = line.at(0);

        // Process the line according to first char
        if (firstChar == '#') {
            // Line is a comment, no processing needed
        } else if (firstChar == 'H') {
            // Line has height data in format "H:##"
            // Strip line to characters representing number and convert
            bool ok; // To check success of toInt()
            int height = line.sliced(2).toInt(&ok);

            // If height is valid, store it in m_settings
            if (height > 0 && ok) {
                m_settings.replace(1, height);
                h = true;
            }
        } else if (firstChar == 'L') {
            // Line has loopingBorders data in format "L:#" where # is either
            // 0 for false or 1 for true
            // Same logic as 'H' case
            bool ok;
            int loopingBorders = line.sliced(2, 1).toInt(&ok);

            if ((loopingBorders == 0 || loopingBorders == 1) && ok) {
                m_settings.replace(0, loopingBorders);
                l = true;
            }
        } else if (firstChar == 'W') {
            // Line has width data in format "W:##"
            // Same logic as 'H' case
            bool ok;
            int width = line.sliced(2).toInt(&ok);

            if (width > 0 && ok) {
                m_settings.replace(2, width);
                w = true;
            }
        } else if (firstChar == '.' || firstChar == 'O') {
            // Line is the start of the data
            // Breaking out of while loop
            ds = true;
        } // End line processing

    } // End header read loop

    // Check if header was read successfully
    if (!(h && l && w)) {
        // If not, clear the buffer and return
        clearBuffer();
        return false;
    }

    // Edit environment to reflect settings read from file
    if (loopingBorders() == 0) {
        environment->setLoopingBorders(false);
    } else {
        environment->setLoopingBorders(true);
    }
    environment->setHeight(height());
    environment->setWidth(width());

    // Create variable to track what line is being processed
    int y = 0;

    // Create boolean to check if every element has been successfully filled
    bool allFull = false;

    while (!input.atEnd()) {
        // Get the line
        line = input.readLine();
        QChar c;

        // Loop over each character
        for (int x = 0; x < width(); x++) {
            // Check range and set variable c if in range
            if (x < line.length()) {
                c = line.at(x);
            } else {
                // Invalid data section formatting, clear buffer and return
                clearBuffer();
                return false;
            }

            // Check the if the character if valid
            // If so set state of corresponding cell in environment
            if (c == '.') {
                environment->cellAt(x, y)->setCurrentState(false);
            } else if (c == 'O') {
                environment->cellAt(x, y)->setCurrentState(true);
            } else {
                // Invalid character, stop processing
                clearBuffer();
                return false;
            }

            // If done processing data, set allFull flag
            if (x == width() - 1 && y == height() - 1) allFull = true;
        }

        // Increment y for the next line
        y++;
    } // End data section read loop

    // Check if buffer successfully filled
    if (!allFull) {
        // If not, clear buffer and return false
        clearBuffer();
        return false;
    }

    f.close();

    return true;
}

bool SaveFileHandler::saveEnvironment(Environment *environment)
{
    // Get settings into m_bufferSettings
    if (environment->loopingBorders()) {
        m_settings.replace(0, 1);
    } else {
        m_settings.replace(0, 0);
    }

    m_settings.replace(1, environment->height());

    m_settings.replace(2, environment->width());

    // Create QFile object
    QString fp = m_directory.absolutePath() + "/" + m_filename;
    QFile f(fp);

    // Check if file can be opened
    if (!f.open(QIODevice::WriteOnly)) {
        clearBuffer();
        return false;
    }

    // Create QTextStream object to write to
    QTextStream fs(&f);

    // Write header of file
    fs << "L:" << loopingBorders() << "\n";
    fs << "H:" << height() << "\n";
    fs << "W:" << width() << "\n";

    qDebug() << "\twriting file data\n";

    // Loop over environment's Cells from top to bottom
    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < width(); x++) {
            if (environment->cellAt(x,y)->currentState()) {
                fs << "O";
            } else {
                fs << ".";
            }
        }
        fs << "\n";
    }

    f.close();

    return true;
}
