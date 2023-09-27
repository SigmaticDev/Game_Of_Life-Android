#ifndef CELLMODEL_H
#define CELLMODEL_H

#include <QAbstractItemModel>
#include <QDir>
#include <QHash>
#include <QByteArray>

class Environment;
class EnvironmentBuilder;

class CellModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    enum Roles {
        Living = Qt::UserRole + 1
    };
    Q_ENUM(Roles)

    explicit CellModel(QObject *parent = nullptr);

    Environment* environment() const {return m_environment;}
    void setEnvironment(Environment* environment);

    Q_INVOKABLE bool loopingBorders() const;
    Q_INVOKABLE void setLoopingBorders(const bool &loop);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void stateUpdated();

public slots:
    Q_INVOKABLE void load(QString filename = "save.gol");
    Q_INVOKABLE void save(QString filename = "save.gol");
    Q_INVOKABLE void setSaveDirectory(QString directory = QDir::current().path());

    Q_INVOKABLE void clearAll();
    Q_INVOKABLE void fillWithSoup(qreal density = 0.4);

    Q_INVOKABLE void nextStep();

    Q_INVOKABLE void resize(int height = 1, int width = 1);

private:
    EnvironmentBuilder* m_builder;
    Environment* m_environment;
};

#endif // CELLMODEL_H
