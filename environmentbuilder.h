#ifndef ENVIRONMENTBUILDER_H
#define ENVIRONMENTBUILDER_H

#include <QObject>

#include "rng.h"

class Environment;
class SaveFileHandler;

class EnvironmentBuilder : public QObject
{
    Q_OBJECT
public:
    explicit EnvironmentBuilder(QObject *parent = nullptr);
    ~EnvironmentBuilder();

    bool saveToFile(Environment* environment, QString filename = "save.gol");
    Environment* loadFromFile(QString filename, QObject* owner = nullptr);
    void setSaveDirectory(QString directory);

    Environment* generateBlankEnvironment(int height = 1, int width = 1,
                                          bool loopingBorders = true,
                                          QObject* owner = nullptr);
    Environment* generateSoup(int height = 1, int width = 1,
                              bool loopingBorders = true,
                              qreal density = 0.4,
                              QObject* owner = nullptr);

signals:

private:
    RNG m_rng;
    SaveFileHandler* m_fileHandler;

};

#endif // ENVIRONMENTBUILDER_H
