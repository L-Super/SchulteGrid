#include"Algor.h"
#include"time.h"
void algor(std::vector<int> &numbers)
{

        for (int i = 0; i < 9; i++)
        {
            numbers.push_back(i);
        }
        srand((unsigned)time(NULL));
        for (int i=0;i<rand()%9;i++)
        {
            std::random_shuffle(numbers.begin(), numbers.end());
        }

        for (int j = 0; j < 9; j++)
        {
            std::cout << numbers[j] << " " ;
        }
        std::cout<<std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << numbers[i] << " | " << numbers[i + 3] << " | " << numbers[i + 6] << std::endl;

        }

}
