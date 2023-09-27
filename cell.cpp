#include "cell.h"

#include "environment.h"

Cell::Cell(QObject *parent, bool state, int xCoord, int yCoord)
    : QObject{parent}
    , m_environment(qobject_cast<Environment*>(parent))
    , m_xCoord(xCoord), m_yCoord(yCoord)
    , m_currentState(state)
    , m_nextState(false)
{
}

Cell::~Cell()
{

}

void Cell::setCurrentState(const bool &state)
{
    m_currentState = state;

    return;
}

void Cell::calculateNextState()
{
    int neighborhood = m_environment->neighborhoodAround(m_xCoord, m_yCoord);

    if (m_currentState) {
        if (neighborhood < 2) {
            m_nextState = false;
        } else if (neighborhood > 3) {
            m_nextState = false;
        } else {
            m_nextState = true;
        }
    } else {
        if (neighborhood == 3) {
            m_nextState = true;
        } else {
            m_nextState = false;
        }
    }

    return;
}

void Cell::advanceState()
{
    m_currentState = m_nextState;

    return;
}
