#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator* translator = new QTranslator();
    QString localeName = QLocale::system().name();
    if(translator->load("ru_RU", ":/translations/translation.qm"))
        a.installTranslator(translator);
    MainWindow w;
    w.show();

    return a.exec();
}
