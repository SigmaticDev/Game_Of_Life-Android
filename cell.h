#ifndef CELL_H
#define CELL_H

#include <QObject>

class Environment;

class Cell : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool currentState READ currentState WRITE setCurrentState NOTIFY currentStateChanged)

public:
    explicit Cell(QObject *parent = nullptr,
                  bool state = false,
                  int xCoord = -1, int yCoord = -1);
    ~Cell();

    Environment* environment() const {return m_environment;}
    int xCoord() const {return m_xCoord;}
    int yCoord() const {return m_yCoord;}
    bool currentState() const {return m_currentState;}

    void setEnvironment(Environment* environment);
    void setXCoord(int xCoord);
    void setYCoord(int yCoord);
    void setCurrentState(const bool &state);

    void calculateNextState();
    void advanceState();

signals:
    void currentStateChanged(bool state);

private:
    Environment* m_environment;

    int m_xCoord;
    int m_yCoord;

    bool m_currentState;
    bool m_nextState;

};

#endif // CELL_H
