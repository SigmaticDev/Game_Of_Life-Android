#include "cellmodel.h"

#include "cell.h"
#include "environment.h"
#include "environmentbuilder.h"

CellModel::CellModel(QObject *parent)
    : QAbstractItemModel{parent}
    , m_builder(new EnvironmentBuilder(this))
    , m_environment(new Environment(this, 10, 10))
{
}

void CellModel::setEnvironment(Environment *environment)
{
    emit layoutAboutToBeChanged({});

    delete m_environment;
    m_environment = environment;

    emit layoutChanged({});
    emit stateUpdated();

    return;
}

bool CellModel::loopingBorders() const
{
    return m_environment->loopingBorders();
}

void CellModel::setLoopingBorders(const bool &loop)
{
    m_environment->setLoopingBorders(loop);
}

int CellModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_environment->height();
}

int CellModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_environment->width();
}

QVariant CellModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    const Cell* cell = m_environment->cellAt(index.column(), index.row());

    switch (role) {
    case Roles::Living:
        return cell->currentState();
    case Qt::DisplayRole:
        return QString()
                .append("[")
                .append(QString::number(index.column()))
                .append(", ")
                .append(QString::number(index.row()))
                .append("]");
    case Qt::ToolTipRole:
        return QString()
                .append("[")
                .append(QString::number(index.column()))
                .append(", ")
                .append(QString::number(index.row()))
                .append("]");
    default:
        return QVariant();
    }
}

bool CellModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) return false;

    if (role != Roles::Living) {
        return false;
    } else {
        Cell* cell = m_environment->cellAt(index.column(), index.row());
        cell->setCurrentState(value.toBool());
        emit dataChanged(index, index, {Living});
        return true;
    }
}

QModelIndex CellModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return createIndex(row, column);
}

QModelIndex CellModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return QModelIndex();
}

QHash<int, QByteArray> CellModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::Living] = "living";
    return roles;
}

Qt::ItemFlags CellModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void CellModel::load(QString filename)
{
    emit layoutAboutToBeChanged({});
    delete m_environment;
    m_environment = m_builder->loadFromFile(filename, this);
    emit layoutChanged({});
    emit dataChanged(createIndex(0, 0, m_environment->cellAt(0, 0)),
                     createIndex(m_environment->height() - 1, m_environment->width() - 1,
                                 m_environment->cellAt(m_environment->width() - 1,
                                                       m_environment->height() - 1)),
                     {Living});
    emit stateUpdated();

    return;
}

void CellModel::save(QString filename)
{
    m_builder->saveToFile(m_environment, filename);

    return;
}

void CellModel::setSaveDirectory(QString directory)
{
    m_builder->setSaveDirectory(directory);

    return;
}

void CellModel::clearAll()
{
    Environment* env = m_builder->generateBlankEnvironment(m_environment->height(),
                                                          m_environment->width(),
                                                          m_environment->loopingBorders(),
                                                          this);

    delete m_environment;
    m_environment = env;

    emit dataChanged(createIndex(0, 0),
                     createIndex(m_environment->height() - 1, m_environment->width() - 1),
                     {Living});
    emit stateUpdated();

    return;
}

void CellModel::fillWithSoup(qreal density)
{
    Environment* env = m_builder->generateSoup(m_environment->height(),
                                               m_environment->width(),
                                               m_environment->loopingBorders(),
                                               density,
                                               this);

    delete m_environment;
    m_environment = env;

    emit dataChanged(createIndex(0, 0),
                     createIndex(m_environment->height() - 1, m_environment->width() - 1),
                     {Living});
    emit stateUpdated();

    return;
}

void CellModel::nextStep()
{
    m_environment->update();

    emit dataChanged(createIndex(0, 0),
                     createIndex(m_environment->height() - 1, m_environment->width() - 1),
                     {Living});
    emit stateUpdated();

    return;
}

void CellModel::resize(int height, int width)
{
    int smallerHeight, smallerWidth;
    if (height < m_environment->height()) {
        smallerHeight = height;
    } else {
        smallerHeight = m_environment->height();
    }
    if (width < m_environment->width()) {
        smallerWidth = width;
    } else {
        smallerWidth = m_environment->width();
    }

    emit layoutAboutToBeChanged({});

    m_environment->addColumns(width - m_environment->width());
    m_environment->addRows(height - m_environment->height());

    emit layoutChanged({});
    emit dataChanged(createIndex(0, 0),
                     createIndex(smallerHeight - 1, smallerWidth - 1),
                     {Living});
    emit stateUpdated();

    return;
}
