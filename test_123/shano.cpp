#include <iostream>
#include <vector>
using namespace std;


class MakeFinal
{
  ~MakeFinal() {} // private by default.
  friend class sealed;
};


class sealed : virtual MakeFinal
{ };

class test : public sealed
{ };

template <int N> struct Fib {
    enum {
        value = Fib<N - 1>::value + Fib<N - 2>::value
    };
};

template <> struct Fib<1> {
    enum { value = 1 };
};

template <> struct Fib<2> {
    enum { value = 1 };
};

enum ENUMTEST
{
  ZERO 	= 0,
  ONE 	= 1,
  TWO 	= 2
};

ENUMTEST a[]={ ONE, TWO, ZERO };

class VisualizableVector
{
  public:
    class proxy
    {
      public:
      proxy ( vector<int>* v ) : vect ( v )
      {
	std::cout << "Before size is: " << vect->size ();
      }
      vector<int> * operator->()
      {
	return vect;
      }
      ~proxy ()
      {
	std::cout << "After size is: " << vect->size ();
      }
      private:
	vector <int> * vect;
    };
    VisualizableVector( vector<int> *v ) : vect( v ) {}
    
    proxy operator->()
    {
      return proxy (vect);
    }

  private:
    vector<int>* vect;
};

namespace xxx
{
  namespace yyy
  {
    const int a = 1;
  }

  enum ALA_BALA
  {
    a = yyy::a,
    b = 2,
    c = 3
  };
}

const int x = 12;

int main()
{
  enum XXX
  {
    x = x,
    y = 13,
    z = 14,
  };
  
  cout << XXX::x << endl;
  cout << a << endl;
}

// int main()
// {
//   VisualizableVector v( new vector<int> );
//   //...
//   v->push_back( 10 ); // Note use of -> operator instead of . operator
//   v->push_back( 20 );
// }

// int main (void)
// {
//   //test t; // Compilation error here.
// 
//   int x = Fib<10>::value; // 55
//   cout << x << endl;
//   
//   int y = Fib<14>::value; // 377
//   cout << y << endl;
// 
//   int i = -15;
//   ENUMTEST eTest = static_cast<ENUMTEST>(i);
//   
//   cout << "eTest=" << eTest << endl;
// 
//   cout << sizeof(a)/sizeof(ENUMTEST) << endl;
//   return 0;
// }
// 
