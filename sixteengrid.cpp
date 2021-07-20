#include "sixteengrid.h"
#include "ui_sixteengrid.h"
#include "NumRand.h"
#include "selector.h"

SixteenGrid::SixteenGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SixteenGrid)
{
    ui->setupUi(this);
    //QPixmap pixmap = QPixmap(":/UI/UiSettings/blackground.png").scaled(this->size());
    QPixmap pixmap = QPixmap(":/UI/UiSettings/blackground1.jpg").scaled(this->size());
    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette( palette );

    // 获取所有QLabel 设置文本为"T"
    QList<QLabel*> label = this->findChildren<QLabel *>();
    for (int i=0;i<label.count();i++)
        label.at(i)->setText("T");

}

SixteenGrid::~SixteenGrid()
{
    delete ui;
}

void SixteenGrid::displaynum()
{
    QVector<int> num;
    for (int i=0;i<16;++i) {
        num.push_back(i+1);
    }
    numrand randnum;
    randnum.AlgoRand(num);
    QList<QLabel*> label = this->findChildren<QLabel *>();
    for (int i=0;i<label.count();i++)
        label.at(i)->setNum(num[i]);
}

void SixteenGrid::on_pushButton_2_clicked()
{
    displaynum();
}

void SixteenGrid::on_pushButton_clicked()
{
    this->hide();
    Selector* s = new Selector;
    s->show();
}
