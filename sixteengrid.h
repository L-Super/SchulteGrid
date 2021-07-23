#ifndef SIXTEENGRID_H
#define SIXTEENGRID_H

#include <QWidget>
#include <QTime>

namespace Ui {
class SixteenGrid;
}

class SixteenGrid : public QWidget
{
    Q_OBJECT

public:
    explicit SixteenGrid(QWidget *parent = nullptr);
    ~SixteenGrid();
    void displaynum();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void updateTimeAndDisplay();

private:
    Ui::SixteenGrid *ui;
    QTimer *ptimer;
    QTime baseTime;
    QString showStr;
};

#endif // SIXTEENGRID_H
