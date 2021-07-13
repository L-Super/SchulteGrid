#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    void refresh();


private slots:
    void on_startBtn_clicked();

    void on_endBtn_clicked();

private:
    Ui::MainMenu *ui;
    //QElapsedTimer *timer;
};
#endif // MAINMENU_H
