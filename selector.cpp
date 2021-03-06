#include "selector.h"
#include "ui_selector.h"

Selector::Selector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selector)
{
    ui->setupUi(this);
    this->ui->label->setStyleSheet("color:white;");
    ui->nineBtn->setStyleSheet("color:white;");
    ui->sixteenBtn->setStyleSheet("color:white;");
    // 去掉问号，只保留关闭
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

Selector::~Selector()
{
    delete ui;
}

void Selector::on_nineBtn_clicked()
{
    this->hide();
    MainMenu* mainwidow = new MainMenu;
    mainwidow->show();
}

void Selector::on_sixteenBtn_clicked()
{
    this->hide();
    SixteenGrid* sixteenWindow = new SixteenGrid;
    sixteenWindow->show();
}
