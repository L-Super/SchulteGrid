#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "NumRand.h"
#include "selector.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setWindowTitle(QString("9宫格 - 舒尔特方格"));
    QPixmap blackground = QPixmap(":/UI/UiSettings/blackground2.jpg").scaled(this->size());
    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background, QBrush(blackground));
    this->setPalette( palette );

//    Qt::IgnoreAspectRatio, Qt::SmoothTransformation  // 饱满填充
//    Qt::KeepAspectRatio, Qt::SmoothTransformation  // 按比例缩放
    QPixmap pixmap = QPixmap(":/UI/UiSettings/time.png").scaled(ui->imglabel->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->imglabel->setPixmap(pixmap);
    ui->imglabel->setAlignment(Qt::AlignCenter);
    //设置窗口背景色
//    setPalette(QPalette(QColor(32,73,105)));
//    setAutoFillBackground(true);

//    QPalette pe;
//    pe.setColor(QPalette::WindowText,QColor(254,212,128));
//    ui->label_1->setPalette(pe);

    //color 设定前景色，就是字体的颜色
    //background 设定后景色，就是按钮的背景的颜色
    //border-radius设定边框的弧度
    // 移至ui qss
    //QString button_style="QPushButton{color:white;background-color:rgb(16,37,53);"
    //                     "border-style: outset;border-radius:5px;padding: 6px;}";
    //    ui->startBtn->setStyleSheet(button_style);
    //    ui->endBtn->setStyleSheet(button_style);

    this->ptimer = new QTimer;
    connect(this->ptimer,SIGNAL(timeout()),this,SLOT(updateTimeAndDisplay()));
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::refresh()
{
    QVector<int> num;
    for (int i=0;i<9;++i) {
        num.push_back(i+1);
    }
    numrand::AlgoRand(num);
//    AlgoRand(num);

    ui->label_1->setText(QString::number(num[0]));
    ui->label_2->setText(QString::number(num[1]));
    ui->label_3->setText(QString::number(num[2]));
    ui->label_4->setText(QString::number(num[3]));
    ui->label_5->setText(QString::number(num[4]));
    ui->label_6->setText(QString::number(num[5]));
    ui->label_7->setText(QString::number(num[6]));
    ui->label_8->setText(QString::number(num[7]));
    ui->label_9->setText(QString::number(num[8]));
}


void MainMenu::on_startBtn_clicked()
{
    static QTime pauseTime;
    // 设置property，按钮实现状态切换
    if(ui->startBtn->property("status") == "stop")
    {
        ui->startBtn->setProperty("status", "start");
        ui->startBtn->setText("开始");
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
        ui->startBtn->setProperty("status", "stop");
        ui->startBtn->setText("停止");
    }

    refresh();
}


void MainMenu::on_endBtn_clicked()
{
    this->hide();
    Selector* s = new Selector;
    s->show();
}

void MainMenu::updateTimeAndDisplay()
{
    QTime current = QTime::currentTime();
    auto t = this->baseTime.msecsTo(current); //从基准时间到现在过了多少毫秒
    QTime showTime(0,0,0,0);
    showTime =showTime.addMSecs(t);
    showStr = showTime.toString("hh:mm:ss:zzz");
    this->ui->lcdNumber->display(showStr);
}
