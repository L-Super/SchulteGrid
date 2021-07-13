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
    this->setWindowTitle(QString("9宫格"));
    //设置窗口背景色
    // 黑色 32,73,105 16,37,53
    // 橙色 254,212,128
    setPalette(QPalette(QColor(32,73,105)));
    setAutoFillBackground(true);
    QPalette pe;
    pe.setColor(QPalette::WindowText,QColor(254,212,128));
//    ui->label_1->setPalette(pe);
//    ui->label_2->setPalette(pe);
//    ui->label_3->setPalette(pe);
//    ui->label_4->setPalette(pe);
//    ui->label_5->setPalette(pe);
//    ui->label_6->setPalette(pe);
//    ui->label_7->setPalette(pe);
//    ui->label_8->setPalette(pe);
//    ui->label_9->setPalette(pe);

    //color 设定前景色，就是字体的颜色
    //background 设定后景色，就是按钮的背景的颜色
    //border-radius设定边框的弧度
    QString button_style="QPushButton{color:white;background-color:rgb(16,37,53);"
                         "border-style: outset;border-radius:5px;padding: 6px;}";

    //    ui->startBtn->setStyleSheet(button_style);
    //    ui->endBtn->setStyleSheet(button_style);

    QObjectList cs = this->children();//访问当前MainMenu子节点控件
    qDebug()<< this->objectName();//获取控件对象名字

    QObjectList pblist=this->ui->splitter->children();
    for (int i = 0; i < pblist.size(); i++)
        {
            qDebug() << "splitter: "<<pblist[i]->objectName();
        }

    const QMetaObject *mobj = this->ui->horizontalLayout_5->metaObject();//获取控件对象类型
    qDebug() << "控件对象类型:" << mobj->className() << endl;
    QString cName = mobj->className();
    if (cName == "QPushButton")
    {
        QPushButton *pb = qobject_cast<QPushButton *>(this);
        if (pb)
        {
            pb->setStyleSheet(button_style);
        }
    }
    else if(cName == "QLabel")
    {
        QLabel* label= qobject_cast<QLabel *>(this);
        if(label)
            label->setPalette(pe);
    }

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
    // 后期考虑只用一个按钮实现开始，停止切换
    ui->startBtn->setText(QString::fromUtf8("停止"));

    //this->timer->start();

    //auto updatetime = timer->elapsed();
//    ui->lcdNumber->display(double(timer->elapsed()));
    refresh();

}


void MainMenu::on_endBtn_clicked()
{
    //ui->lcdNumber->display(double(timer->elapsed()));
    //this->timer->restart();


}