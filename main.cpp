#include "mainmenu.h"
#include "selector.h"
#include "mainmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu w;
    Selector selectors;

//    if(selectors.exec()==QDialog::accept())
//    {
//        w.show();
//        return a.exec();
//    }
//    else if()
    selectors.show();
    w.show();
    return a.exec();
}
