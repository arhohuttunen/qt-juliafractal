#include <QApplication>
#include "FractalWidget.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("fractal");
    app.setOverrideCursor(Qt::BlankCursor);

    FractalWidget widget;
    widget.resize(800, 480);
    widget.showFullScreen();

    return app.exec();
}
