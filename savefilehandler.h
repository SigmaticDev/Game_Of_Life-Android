#ifndef SAVEFILEHANDLER_H
#define SAVEFILEHANDLER_H

#include <QDir>
#include <QFile>
#include <QObject>
#include <QVector>

class Cell;
class Environment;

class SaveFileHandler : public QObject
{
    Q_OBJECT
public:
    explicit SaveFileHandler(QObject *parent = nullptr);
    ~SaveFileHandler();

    QDir directory() const {return m_directory;}
    QString filename() const {return m_filename;}
    int height() const {return m_settings[1];}
    bool loopingBorders() const {return m_settings[0];}
    int width() const {return m_settings[2];}

    void setDirectory(QDir directory);
    void setFilename(QString filename);

    void clearBuffer();
    bool loadFromFile(Environment* environment);
    bool saveEnvironment(Environment* environment);

signals:

private:
    QList<int> m_settings;
    QDir m_directory;
    QString m_filename;

};

#endif // SAVEFILEHANDLER_H
