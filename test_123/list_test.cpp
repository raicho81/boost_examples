#include <list>
#include <random>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

std::mt19937 generator;
std::uniform_int_distribution<int> distribution(1, 1000*1000);
auto rand_int = bind( distribution, generator );  // generates number in the range 1..1000000
  
int main(int argc, char** argv)
{
  list<int> test_list;

  for( int i = 0; i < 1024*1024*4; ++i)
  {
    test_list.push_back(rand_int());
  }

  ofstream os("test_list.out");
  
  for(auto elm: test_list) // traverse
  {
    os << elm << endl;
  }

  return 0;
}
