#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cellmodel.h"
#include "environment.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CellModel model = CellModel(&engine);

    model.resize(40, 40);
    model.environment()->setLoopingBorders(true);
    model.fillWithSoup(0.2);

//    engine.rootContext()->setContextProperty("cellModel", &model);

    QQmlContext* context = engine.rootContext();
    context->setContextProperty("cellModel", &model);

//    QQmlContext* context = new QQmlContext(engine.rootContext());
//    context->setContextProperty("cellModel", &model);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
