#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QObject>

class Cell;

class Environment : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool loopingBorders READ loopingBorders WRITE setLoopingBorders NOTIFY loopingBordersChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)

public:
    explicit Environment(QObject *parent = nullptr,
                         int height = 1, int width = 1);

    bool loopingBorders() const {return m_loopingBorders;}
    int height() const {return m_height;}
    int width() const {return m_width;}
    Cell* cellAt(int xCoord, int yCoord) const {return m_cells[xCoord][yCoord];}

    void setLoopingBorders(const bool &loop);
    void setHeight(const int &height);
    void setWidth(const int &width);
    void setCellAt(int xCoord, int yCoord, Cell* cell);

    void addColumns(int number = 1);
    void addRows(int number = 1);
    void removeColumns(int number = 1);
    void removeRows(int number = 1);

    int neighborhoodAround(int xCoord, int yCoord) const;

    void update();

signals:
    void heightChanged();
    void loopingBordersChanged();
    void updated();
    void widthChanged();

private:
    void deleteAllCells();
    int normedX(int x) const;
    int normedY(int y) const;

private:
    bool m_loopingBorders;

    int m_height;
    int m_width;

    QVector<QVector<Cell*> > m_cells;

};

#endif // ENVIRONMENT_H
