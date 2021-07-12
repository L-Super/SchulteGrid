#include"NumRand.h"
#include<ctime>
#include<iostream>
#include <algorithm>
int random (int i)
{
    return std::rand()%i;
}

void numrand::AlgoRand(QVector<int> &num)
{
    //vector<int> num;
//    for(int i=1;i<10;i++)
//    {
//        num.push_back(i);
//    }

    srand((int)time(NULL));
    //auto random=rand();
    std::random_shuffle(num.begin(),num.end(),random);
    for(auto s:num)
        std::cout<<s<<" ";
    std::cout<<std::endl;
    //return  num;

}
