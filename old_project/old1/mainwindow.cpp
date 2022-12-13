#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Algor.h"
#include<QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口背景色
    setPalette(QPalette(QColor(255,156,156)));
    setAutoFillBackground(true);
    QPalette pe;
        pe.setColor(QPalette::WindowText,QColor(132,133,121));

    std::vector<int> numbers;
    algor(numbers);
//    for (int i=0;i<9;++i) {
//        //QString text=numbers[i];
//        int j=i+1;
//        //QString label=("label_"+QString::number(i+1));
//        ui->label[j]->setText(QString::number(numbers[i]));
//    }
    //ui->label_1->setText();

    ui->label_1->setText(QString::number(numbers[0]));
    ui->label_1->setPalette(pe);
    ui->label_2->setText(QString::number(numbers[1]));
    ui->label_2->setPalette(pe);
    ui->label_3->setText(QString::number(numbers[2]));
    ui->label_3->setPalette(pe);
    ui->label_4->setText(QString::number(numbers[3]));
    ui->label_4->setPalette(pe);
    ui->label_5->setText(QString::number(numbers[4]));
    ui->label_5->setPalette(pe);
    ui->label_6->setText(QString::number(numbers[5]));
    ui->label_6->setPalette(pe);
    ui->label_7->setText(QString::number(numbers[6]));
    ui->label_7->setPalette(pe);
    ui->label_8->setText(QString::number(numbers[7]));
    ui->label_8->setPalette(pe);
    ui->label_9->setText(QString::number(numbers[8]));
    ui->label_9->setPalette(pe);
    ui->pushButton_1->setPalette(pe);
    ui->pushButton_2->setPalette(pe);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    std::vector<int> numbers;
    algor(numbers);

    MainWindow::ui->label_1->setText(QString::number(numbers[0]));

    MainWindow::ui->label_2->setText(QString::number(numbers[1]));

    MainWindow::ui->label_3->setText(QString::number(numbers[2]));

    MainWindow::ui->label_4->setText(QString::number(numbers[3]));

    MainWindow::ui->label_5->setText(QString::number(numbers[4]));

    MainWindow::ui->label_6->setText(QString::number(numbers[5]));

    MainWindow::ui->label_7->setText(QString::number(numbers[6]));

    MainWindow::ui->label_8->setText(QString::number(numbers[7]));

    MainWindow::ui->label_9->setText(QString::number(numbers[8]));

}
void MainWindow::on_pushButton_1_clicked()
{
    refresh();
}
