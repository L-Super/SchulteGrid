#ifndef SELECTOR_H
#define SELECTOR_H

#include <QDialog>
#include "mainmenu.h"
#include "sixteengrid.h"

namespace Ui {
class Selector;
}

class Selector : public QDialog
{
    Q_OBJECT

public:
    explicit Selector(QWidget *parent = nullptr);
    ~Selector();

private slots:
    void on_nineBtn_clicked();

    void on_sixteenBtn_clicked();

private:
    Ui::Selector *ui;
};

#endif // SELECTOR_H
