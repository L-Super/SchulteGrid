#include"AlgorithmRandom.h"

int AlgoRand(vector<int> &num)
{
    //vector<int> num;
    for(int i=1;i<10;i++)
    {
        num.push_back(i);
    }
    random_shuffle(num.begin(),num.end());
    for(auto s:num)
        cout<<s<<" ";
    //return  num;

}
