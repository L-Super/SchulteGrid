#include "selector.h"
#include "ui_selector.h"

Selector::Selector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selector)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("SchulteGrid"));
    this->setStyleSheet("background-color:rgb(16,37,53);");
    this->ui->label->setStyleSheet("color:white;");
    ui->nineBtn->setStyleSheet("color:white;");
    ui->sixteenBtn->setStyleSheet("color:white;");
}

Selector::~Selector()
{
    delete ui;
}
