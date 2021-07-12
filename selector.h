#ifndef SELECTOR_H
#define SELECTOR_H

#include <QDialog>

namespace Ui {
class Selector;
}

class Selector : public QDialog
{
    Q_OBJECT

public:
    explicit Selector(QWidget *parent = nullptr);
    ~Selector();

private:
    Ui::Selector *ui;
};

#endif // SELECTOR_H
