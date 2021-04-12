#include "start.h"
#include"ninemainui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
    w.show();
//    NineMainUi *mi=new NineMainUi;
//    mi->show();
    return a.exec();
}
