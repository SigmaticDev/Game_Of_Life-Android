#include "environment.h"

#include "cell.h"

Environment::Environment(QObject *parent, int height, int width)
    : QObject{parent}
    , m_loopingBorders(false)
    , m_height(1)
    , m_width(1)
    , m_cells(QVector<QVector<Cell*> >(1, QVector<Cell*>(1, new Cell(this, false, 0, 0))))
{
    addColumns(width - 1);
    addRows(height - 1);
}

void Environment::setLoopingBorders(const bool &loop)
{
    m_loopingBorders = loop;

    emit loopingBordersChanged();

    return;
}

void Environment::setHeight(const int &height)
{
    addRows(height - m_height);

    return;
}

void Environment::setWidth(const int &width)
{
    addColumns(width - m_width);

    return;
}

void Environment::setCellAt(int xCoord, int yCoord, Cell *cell)
{
    m_cells[xCoord].replace(yCoord, cell);

    return;
}

void Environment::addColumns(int number)
{
    if (number == 0) return;
    if (number < 0) return removeColumns(-number);

    for (int x = m_width; x < (m_width + number); x++) {
        m_cells.append(QVector<Cell*>());

        for (int y = 0; y < m_height; y++) {
            m_cells[x].append(new Cell(this, false, x, y));
        }
    }

    m_width += number;

    emit widthChanged();

    return;
}

void Environment::addRows(int number)
{
    if (number == 0) return;
    if (number < 0) return removeRows(-number);

    for (int y = m_height; y < (m_height + number); y++) {

        for (int x = 0; x < m_width; x++) {
            m_cells[x].append(new Cell(this, false, x, y));
        }
    }

    m_height += number;

    emit heightChanged();

    return;
}

void Environment::removeColumns(int number)
{
    if (number == 0) return;
    if (number < 0) return addColumns(-number);
    if (number >= m_width) {
        deleteAllCells();

        m_cells = QVector<QVector<Cell*> >(1, QVector<Cell*>(1, new Cell(this, false, 0, 0)));
        m_height = 1;
        m_width = 1;
        return;
    }

    for (int x = m_width - 1; x >= (m_width - number); x--) {
        // Delete each cell in the column
        for (int y = 0; y < m_height; y++) {
            delete m_cells[x][y];
        }
        // Remove the column
        m_cells.removeLast();
    }

    m_width -= number;

    emit widthChanged();

    return;
}

void Environment::removeRows(int number)
{
    if (number == 0) return;
    if (number < 0) return addRows(-number);
    if (number >= m_height) {
        deleteAllCells();

        m_cells = QVector<QVector<Cell*> >(1, QVector<Cell*>(1, new Cell(this, false, 0, 0)));
        m_height = 0;
        m_width = 0;
        return;
    }

    // Row by row from the current last row
    for (int y = m_height - 1; y >= (m_height - number); y--) {
        // For each column
        for (int x = 0; x < m_width; x++) {
            // Delete the cell and resize the vector by 1
            delete m_cells[x][y];
            m_cells[x].removeLast();
        }
    }

    m_height -= number;

    emit heightChanged();

    return;
}

int Environment::neighborhoodAround(int xCoord, int yCoord) const
{
    int result = 0;

    int nX, nY;

    // Top left
    nX = normedX(xCoord-1);
    nY = normedY(yCoord-1);

    if (nX != -1 && nY != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Top
    nX = xCoord;

    if (nY != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Top right
    nX = normedX(xCoord+1);

    if (nX != -1 && nY != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Left
    nX = normedX(xCoord-1);
    nY = yCoord;

    if (nX != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Right
    nX = normedX(xCoord+1);

    if (nX != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Bottom left
    nX = normedX(xCoord-1);
    nY = normedY(yCoord+1);

    if (nX != -1 && nY != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Bottom
    nX = xCoord;

    if (nY != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    // Bottom right
    nX = normedX(xCoord+1);

    if (nX != -1 && nY != -1) {

        if (m_cells[nX][nY]->currentState()) result++;
    }

    return result;
}

void Environment::update()
{
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            m_cells[x][y]->calculateNextState();
        }
    }

    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            m_cells[x][y]->advanceState();
        }
    }

    return;
}

void Environment::deleteAllCells()
{
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            delete m_cells[x][y];
            setCellAt(x, y, nullptr);
        }
    }

    return;
}

int Environment::normedX(int x) const
{
    if (x <= -1) {

        if (m_loopingBorders) {
            return m_width - 1;
        } else {
            return -1;
        }

    } else if (x >= m_width) {

        if (m_loopingBorders) {
            return 0;
        } else {
            return -1;
        }

    } else {

        return x;

    }
}

int Environment::normedY(int y) const
{
    if (y <= -1) {

        if (m_loopingBorders) {
            return m_height - 1;
        } else {
            return -1;
        }

    } else if (y >= m_height) {

        if (m_loopingBorders) {
            return 0;
        } else {
            return -1;
        }

    } else {

        return y;

    }
}
