#ifndef START_H
#define START_H

#include <QMainWindow>
#include"ninemainui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Start; }
QT_END_NAMESPACE

class Start : public QMainWindow
{
    Q_OBJECT

public:
    Start(QWidget *parent = nullptr);
    ~Start();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Start *ui;
    //NineMainUi *mi;
};
#endif // START_H
