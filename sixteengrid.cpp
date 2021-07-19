#include "sixteengrid.h"
#include "ui_sixteengrid.h"
#include "NumRand.h"
#include "selector.h"

SixteenGrid::SixteenGrid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SixteenGrid)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap(":/UI/UiSettings/blackground.png").scaled(this->size());
    QPalette palette (this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette( palette );

    const QMetaObject *mobj = this->metaObject();//获取控件对象类型
    qDebug() << "控件对象类型:" << mobj->className() << endl;
    QString cName = mobj->className();

//    QList<QLineEdit *> lineEdit=ui->tabWidget->findChildren<QLineEdit *>();
//        for (int i=0;i<lineEdit.count();i++)
//        lineEdit.at(i)->setText("www.hicjiajia.cn");

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
    numrand* randnum;
    randnum->AlgoRand(num);
}

void SixteenGrid::on_pushButton_2_clicked()
{
    displaynum();
}
