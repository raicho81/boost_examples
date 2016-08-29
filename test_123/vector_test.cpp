#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
  std::mt19937 generator;
  std::uniform_int_distribution<int> distribution(1, 1000*1000);
  auto dice = std::bind ( distribution, generator );  // generates number in the range 1..1000000

  vector<int> test_vector;

  for( int i = 0; i < 1024*1024; ++i)
  {
    int dice_roll = dice();
//    cout << "dice_roll=" << dice_roll << endl;
    test_vector.push_back(dice_roll);
  }

  // sort(test_vector.begin(), test_vector.end());
  
  ofstream os("test.out");
  
  for(auto elm: test_vector) // traverse
  {
    os << elm << endl;
  }
  
  return 0;
}
