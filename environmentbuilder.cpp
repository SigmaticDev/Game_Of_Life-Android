#include "environmentbuilder.h"

#include <QDir>

#include "cell.h"
#include "environment.h"
#include "savefilehandler.h"

EnvironmentBuilder::EnvironmentBuilder(QObject *parent)
    : QObject{parent}
    , m_rng(RNG(0.0,1.0,0.6))
    , m_fileHandler(new SaveFileHandler(this))
{
}

EnvironmentBuilder::~EnvironmentBuilder()
{
}

bool EnvironmentBuilder::saveToFile(Environment *environment, QString filename)
{
    m_fileHandler->setFilename(filename);

    return m_fileHandler->saveEnvironment(environment);
}

Environment *EnvironmentBuilder::loadFromFile(QString filename, QObject *owner)
{
    Environment* env = new Environment(owner);

    m_fileHandler->setFilename(filename);

    if (m_fileHandler->loadFromFile(env)) {
        return env;
    } else {
        delete env;
        return nullptr;
    }
}

void EnvironmentBuilder::setSaveDirectory(QString directory)
{
    QDir dir = QDir(directory);

    if (dir.exists()) m_fileHandler->setDirectory(dir);

    return;
}

Environment *EnvironmentBuilder::generateBlankEnvironment(int height, int width, bool loopingBorders, QObject *owner)
{
    Environment* env = new Environment(owner, height, width);
    env->setLoopingBorders(loopingBorders);
    return env;
}

Environment *EnvironmentBuilder::generateSoup(int height, int width, bool loopingBorders, qreal density, QObject *owner)
{
    Environment* env = generateBlankEnvironment(height, width, loopingBorders, owner);

    m_rng.setSuccessPercentChance(density * 100);

    for (int x = 0; x < env->width(); x++) {
        for (int y = 0; y < env->height(); y++) {
            env->cellAt(x, y)->setCurrentState(m_rng());
        }
    }

    return env;
}
