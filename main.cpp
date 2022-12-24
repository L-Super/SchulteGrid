#include <QApplication>
#include <QFile>
#include <QIcon>

#include "MenuWidget.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  QFile qss(":/resources/style.css");
  if (qss.open(QFile::ReadOnly)) {
    qApp->setStyleSheet(qss.readAll());
    qss.close();
  } else {
    qDebug("Open failed");
  }

  qApp->setWindowIcon(QIcon(":/resources/whale-logo.png"));

  MenuWidget m;
  m.show();

  return QApplication::exec();
}
