#include "sixteengrid.h"
#include "ui_sixteengrid.h"
#include "NumRand.h"
#include "selector.h"

SixteenGrid::SixteenGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SixteenGrid)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/UI/UiSettings/blackground1.jpg").scaled(this->size());
    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette( palette );

    // 获取所有QLabel 设置文本为"T"
    QList<QLabel*> label = this->findChildren<QLabel *>();
    for (int i=0;i<label.count();i++)
        label.at(i)->setText("T");
    this->ptimer = new QTimer;
    connect(this->ptimer,SIGNAL(timeout()),this,SLOT(updateTimeAndDisplay()));
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
    for (int i=0;i<label.count()-1;i++)
        label.at(i)->setNum(num[i]);
}

void SixteenGrid::on_pushButton_2_clicked()
{
    displaynum();
    QTime pauseTime;
    // 设置property，按钮实现状态切换
    if(ui->pushButton_2->property("status") == "stop")
    {
        ui->pushButton_2->setProperty("status", "start");
        ui->pushButton_2->setText("开始");
        //进行差值计算
        QTime cut = QTime::currentTime();
        auto t = pauseTime.msecsTo(cut);
        qDebug()<<"t: "<<t;
        this->baseTime = this->baseTime.addMSecs(t);
        this->ptimer->stop();
    }
    else
    {
        this->baseTime = QTime::currentTime();
        this->ptimer->start(1);
        ui->pushButton_2->setProperty("status", "stop");
        ui->pushButton_2->setText("停止");
    }
}

void SixteenGrid::on_pushButton_clicked()
{
    this->hide();
    Selector* s = new Selector;
    s->show();
}

void SixteenGrid::updateTimeAndDisplay()
{
    QTime current = QTime::currentTime();
    auto t = this->baseTime.msecsTo(current); //从基准时间到现在过了多少毫秒
    QTime showTime(0,0,0,0);
    showTime =showTime.addMSecs(t);
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
}