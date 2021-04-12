#include "ninemainui.h"
#include "ui_ninemainui.h"
#include"ninemainui.h"
#include"AlgorithmRandom.h"
#include<QGridLayout>
#include<QLabel>
#include<QPushButton>
#include<vector>

NineMainUi::NineMainUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NineMainUi)
{
    ui->setupUi(this);
    QLabel *label1=new QLabel;
    QLabel *label2=new QLabel;
    QLabel *label3=new QLabel;
    QLabel *label4=new QLabel;
    QLabel *label5=new QLabel;
    QLabel *label6=new QLabel;
    QLabel *label7=new QLabel;
    QLabel *label8=new QLabel;
    QLabel *label9=new QLabel;

    vector<int> vec;
    for (int i=1;i<10;i++) {
        vec.push_back(i);
    }
    for(auto c:vec)
        std::cout<<c<<std::endl;

    //AlgoRand(vec);
    label1->setText("vec[1]");


    //网格布局
    //https://www.pianshen.com/article/6048386630/
   QGridLayout *layout=new QGridLayout;


   //QGridLayout::GridLayout.addWidget(&Edit1,0,0);//第0行第0列
//   //GridLayout.addWidget(&label,0,0);//第0行第0列

   layout->addWidget(label1,0,0);
   layout->addWidget(label2,0,1);
   layout->addWidget(label3,1,1);
//还不太清楚怎么使用
//   layout->setRowStretch(1, 1);//设置行比例系数
//   layout->setColumnStretch(1, 1);//设置列比例系数

   this->setLayout(layout);



}

NineMainUi::~NineMainUi()
{
    delete ui;
}
