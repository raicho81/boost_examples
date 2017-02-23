#include <boost/predef.h> // Tools to identify the OS.

#ifdef BOOST_OS_WINDOWS
    #define _WIN32_WINNT 0x0501
   
    #if _WIN32_WINNT <= 0x0502 // Windows Server 2003 or earlier.
        #define BOOST_ASIO_DISABLE_IOCP
        #define BOOST_ASIO_ENABLE_CANCELIO
    #endif
#endif

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
using namespace boost;

int main()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 5000;
    try {
        asio::ip::tcp::endpoint
        ep(asio::ip::address::from_string(raw_ip_address), port_num);
        asio::io_service ios;
        std::shared_ptr<asio::ip::tcp::socket> sock(
        new asio::ip::tcp::socket(ios, ep.protocol()));

        sock->async_connect(ep, [sock](const boost::system::error_code& ec)
        {
            //If asynchronous operation has been
            //cancelled or an error occured during
            //execution, ec contains corresponding
            //error code.
            if (ec != 0) {
                if (ec == asio::error::operation_aborted) {
                    std::cout << "Operation cancelled!" << std::endl;
                }
                else {
                    std::cout << "Error occured!"
                    << " Error code = "
                    << ec.value()
                    << ". Message: "
                    << ec.message() << std::endl;
                }
                return;
            }

            std::cout << "Connected." << std::endl;
            // At this point the socket is connected and
            // can be used for communication with
            // remote application.
        });
        
        // Starting a thread, which will be used
        // to call the callback when asynchronous
        // operation completes.
        std::thread worker_thread([&ios](){
            try {
                ios.run();
            }
            catch (system::system_error &e) {
                std::cout << "Error occured!"
                << " Error code = " << e.code()
                << ". Message: " << e.what();
            }
        });

        // Emulating delay.
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Cancelling the initiated operation.
        sock->cancel();

        // Waiting for the worker thread to complete.
        worker_thread.join();
    }
    catch (system::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
        << ". Message: " << e.what() << std::endl;
        return e.code().value();
    }
    return 0;
}