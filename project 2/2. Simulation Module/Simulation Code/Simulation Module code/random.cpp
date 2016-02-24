#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
using namespace std;
std::default_random_engine generator;
float ND(float mu,float sigma)
{
    normal_distribution<float> distribution(mu,sigma);
    return distribution(generator);
};

int main()
{
  


for (int i=0;i<10;i++){
    std::cout<<ND(0.2,0.4)<<std::endl;
}

}