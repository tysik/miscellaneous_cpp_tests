cmake_minimum_required(VERSION 2.8)
project(miscellaneous_cpp_tests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system thread coroutine context)
include_directories(${Boost_INCLUDE_DIRS})

#
# std
#
add_executable(auto_test std/auto_test.cpp)

add_executable(lambda_test std/lambda_test.cpp)

add_executable(chrono_test std/chrono_test.cpp)

add_executable(async_test std/async_test.cpp)
target_link_libraries(async_test pthread)

add_executable(thread_test std/thread_test.cpp)
target_link_libraries(thread_test pthread)
#set_target_properties(auto_test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)

add_executable(deque_test std/deque_test.cpp)

#
# boost
#

# TIMERS
add_executable(timer1 boost/timers/timer1.cpp)
target_link_libraries(timer1 ${Boost_LIBRARIES})

add_executable(timer2 boost/timers/timer2.cpp)
target_link_libraries(timer2 ${Boost_LIBRARIES})

add_executable(timer3 boost/timers/timer3.cpp)
target_link_libraries(timer3 ${Boost_LIBRARIES})

add_executable(timer4 boost/timers/timer4.cpp)
target_link_libraries(timer4 ${Boost_LIBRARIES})

add_executable(timer5 boost/timers/timer5.cpp)
target_link_libraries(timer5 ${Boost_LIBRARIES})

# TCP UDP
add_executable(tcp_client boost/tcp/tcp_client.cpp)
target_link_libraries(tcp_client ${Boost_LIBRARIES})

add_executable(tcp_server boost/tcp/tcp_server.cpp)
target_link_libraries(tcp_server ${Boost_LIBRARIES})

add_executable(tcp_async_server boost/tcp/tcp_async_server.cpp)
target_link_libraries(tcp_async_server ${Boost_LIBRARIES})

add_executable(udp_client boost/udp/udp_client.cpp)
target_link_libraries(udp_client ${Boost_LIBRARIES})

add_executable(udp_server boost/udp/udp_server.cpp)
target_link_libraries(udp_server ${Boost_LIBRARIES})

add_executable(udp_async_server boost/udp/udp_async_server.cpp)
target_link_libraries(udp_async_server ${Boost_LIBRARIES})

# MISCELLANEOUS
add_executable(steady_timer boost/misc/steady_timer.cpp)
target_link_libraries(steady_timer ${Boost_LIBRARIES})

add_executable(http_client boost/misc/http_client.cpp)
target_link_libraries(http_client ${Boost_LIBRARIES})

add_executable(time_server boost/misc/time_server.cpp)
target_link_libraries(time_server ${Boost_LIBRARIES})

add_executable(coroutines boost/misc/coroutines.cpp)
target_link_libraries(coroutines ${Boost_LIBRARIES})

# THREADS
add_executable(threads_intro boost/thread/threads_intro.cpp)
target_link_libraries(threads_intro ${Boost_LIBRARIES})

add_executable(threads_synchro boost/thread/threads_synchro.cpp)
target_link_libraries(threads_synchro ${Boost_LIBRARIES})
