#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/system/error_code.hpp>
#include <boost/function.hpp>
#include <boost/timer.hpp>
#include <boost/bind.hpp>

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


class A 
{
public:
  virtual void test(int xx){ __attribute__((unused)) int b = 0;}
  int m_iTest = 0;
};

 
struct Foo {
    int n;
    Foo() {
       std::clog << "static constructor\n";
    }
    ~Foo() {
       std::clog << "static destructor\n";
    }
};
 
Foo ff; // static object

class MemLeak
{
  private:
    int* a;

  public:
    MemLeak() throw( std::exception )
    {
      a = new int[10];
      throw std::exception(); // memory leak
    }

    ~MemLeak() throw (std::exception)
    {
      delete [] a;
    }
};

struct CallbackA
{
    void some_f()
    {
        std::cout << "CallbackA::some_f()" << std::endl;
    }
    
    void call_me( boost::system::error_code& ec )
    {
        std::cout << "A::call_me(), ec: " << ec << ", this=" << std::hex << this << std::endl;
        some_f();
    }
};

struct CallbackB
{
    void do_stuff_and_invoke_cb( boost::function<void( boost::system::error_code& )> f )
    {
        boost::system::error_code ecc;
        test123( boost::bind( f, ecc ) );
    }
    
    void test123( boost::function<void()> f )
    {
        f();
    }
};

int main()
{
    CallbackA a;
    CallbackB b;
    b.do_stuff_and_invoke_cb( boost::bind( &CallbackA::call_me, boost::ref( a ), _1 ) );

    return 0;
}


// int main()
// {	
// 	string sParam = "1";
// 	cout << "sParam.empty()=" << sParam.empty() << std::endl;
// 
// 	unsigned int aaaa = boost::lexical_cast < unsigned int >( sParam );
// 	
// 	cout << "aaaa=" << aaaa << std::endl;
// 
// 	for(int i=0; i < 1024; ++i)
// 	{
// 		try
// 		{
// 			MemLeak m;
// 		}
// 		catch(std::exception& e)
// 		{
// 		}
// 	}
// 
// 	std::cout << "main function , " << std::hex << 873453485763845 << std::endl;
// 
//     return 0;
// }

// int main()
// {
//   cout << "sizeof(A) = " << sizeof(A) << endl;
// }

// int main()
// {
//   enum XXX
//   {
//     x = x,
//     y = 13,
//     z = 14,
//   };
//   
//   cout << XXX::x << endl;
//   cout << a << endl;
// }

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
