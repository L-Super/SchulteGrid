#include"AlgorithmRandom.h"
#include<ctime>
int random (int i)
{
    return std::rand()%i;
}

void AlgoRand(std::vector<int> &num)
{
    //vector<int> num;
    for(int i=1;i<10;i++)
    {
        num.push_back(i);
    }

    srand((int)time(NULL));
    //auto random=rand();
    random_shuffle(num.begin(),num.end(),random);
    for(auto s:num)
        cout<<s<<" ";
    cout<<endl;
    //return  num;

}
