//#include "fenprincipale.h"
#include "iostream"
#include "QtWidgets"
#include "windowveditor.h"

int main(int argc, char *argv[])

{

    QApplication app(argc, argv);

    WindowVEditor window(argc, argv);

    QFile file("style.css");
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        QTextCodec *codec = Qt::codecForHtml(data);
        QString str = codec->toUnicode(data);
        app.setStyleSheet(str);
    }

    const QRect availableGeometry = QApplication::desktop()->availableGeometry(&window);
    window.resize(availableGeometry.width() / 2, (availableGeometry.height() * 2) / 3);
    window.move((availableGeometry.width() - window.width()) / 2,
            (availableGeometry.height() - window.height()) / 2);

    window.show();

    return app.exec();

}
