#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);
}

Start::~Start()
{
    delete ui;
}


void Start::on_pushButton_clicked()
{
    this->hide();
    NineMainUi *mi=new NineMainUi;
    mi->show();
    //MainUi mi;
    //mi.exec();
//    mi=new NineMainUi(this);
//    mi->show();

}
