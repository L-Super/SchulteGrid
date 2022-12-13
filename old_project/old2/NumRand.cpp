#include"NumRand.h"
#include <algorithm>
#include <QtCore/QTime>
#include <iostream>
int random (int i)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return qrand()%i;;
}

void numrand::AlgoRand(QVector<int> &num)
{
    std::random_shuffle(num.begin(),num.end(),random);
    for(auto s:num)
        //qDebug()<<" "<<s;自带换行
        std::cout<<s<<" ";
    std::cout<<""<<std::endl;

}
