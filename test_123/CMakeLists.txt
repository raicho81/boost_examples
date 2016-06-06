cmake_minimum_required(VERSION 2.6)
project(test_123)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++11 support. C++11 enabled")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++0x support. C++0x enabled")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(Boost COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_executable(test_123 main.cpp)
add_executable(time_time_asio time_asio.cpp)
add_executable(weak_ptr weak_ptr.cpp)
add_executable(pointers_container pointers_container.cpp)

target_link_libraries(test_123 ${Boost_LIBRARIES})
target_link_libraries(time_time_asio ${Boost_LIBRARIES})
target_link_libraries(weak_ptr ${Boost_LIBRARIES})
target_link_libraries(pointers_container ${Boost_LIBRARIES})

install(TARGETS test_123 RUNTIME DESTINATION bin)
