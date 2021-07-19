#ifndef SIXTEENGRID_H
#define SIXTEENGRID_H

#include <QDialog>

namespace Ui {
class SixteenGrid;
}

class SixteenGrid : public QDialog
{
    Q_OBJECT

public:
    explicit SixteenGrid(QWidget *parent = nullptr);
    ~SixteenGrid();
    void displaynum();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::SixteenGrid *ui;
};

#endif // SIXTEENGRID_H
