#include "mainmenu.h"
#include "selector.h"
#include "mainmenu.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    Selector selectors;
    QFile qss(":/UI/UiSettings/uisetting.qss");
    if( qss.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    else
    {
        qDebug("Open failed");
    }


    selectors.show();
    //w.show();
    return a.exec();
}
