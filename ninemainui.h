#ifndef NINEMAINUI_H
#define NINEMAINUI_H

#include <QDialog>

namespace Ui {
class NineMainUi;
}

class NineMainUi : public QDialog
{
    Q_OBJECT

public:
    explicit NineMainUi(QWidget *parent = nullptr);
    ~NineMainUi();

private:
    Ui::NineMainUi *ui;
};

#endif // NINEMAINUI_H
