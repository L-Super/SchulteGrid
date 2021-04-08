#include "ninemainui.h"
#include "ui_ninemainui.h"
#include<QGridLayout>
#include<QLineEdit>

NineMainUi::NineMainUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NineMainUi)
{
    ui->setupUi(this);
    //网格布局
    //https://www.pianshen.com/article/6048386630/
   QGridLayout GridLayout;
   QLineEdit Edit1;
   //QGridLayout::GridLayout.addWidget(&Edit1,0,0);//第0行第0列
   GridLayout.addWidget(&Edit1,0,0);//第0行第0列
}

NineMainUi::~NineMainUi()
{
    delete ui;
}
