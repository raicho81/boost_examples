#include <iostream>
#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/range.hpp>
#include <boost/function.hpp>

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

class Test;
using memfn = void(Test::*)();

class Test
{
public:
    Test()
    {
        m_workerThread.reset( new boost::thread( boost::bind( &Test::run, this ) ) );
    }

    void StopThread()
    {
        m_bRunning = false;
        m_workerThread->join();
    }

protected:
    bool m_bRunning = true;
    boost::scoped_ptr<boost::thread> m_workerThread;

    void run()
    { 
        while( m_bRunning )
        {
            std::cout << "Running ..." << std::endl;
            boost::this_thread::sleep( boost::posix_time::milliseconds( 500 ) );
        }
    }
};

class A // Abstract class
{
public:
    A(){};
    A(const A&)=delete;
    A& operator=(const A&)=delete;
    virtual void test()=0;
    virtual ~A(){}
};

class B: public A // Subclass A without implementing any of A's abstract method(s) => B is also abstract
{
};
  

int main(int argc, char** argv)
{
    Test t;
    boost::this_thread::sleep( boost::posix_time::seconds( 5 ) );
    std::cout << "Stopping ..." << std::endl;

//    memfn f = &Test::StopThread;
//    CALL_MEMBER_FN(t, f);
    t.StopThread();

   
    std::cout << "Stopped ..." << std::endl;
}