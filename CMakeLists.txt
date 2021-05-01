cmake_minimum_required(VERSION 3.19)
project(double_pendulum)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/Program Files/mingw-w64
                     /x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64
                     /x86_64-w64-mingw32/include")
include_directories("C:/Program Files/mingw-w64
                     /x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/include")

add_executable(double_pendulum main.cpp Pendulum.cpp Pendulum.h Pendulums.cpp Pendulums.h)

target_link_directories(double_pendulum PUBLIC "C:/ProgramFiles/mingw-w64
                        /x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64
                        /x86_64-w64-mingw32/lib")
target_link_directories(double_pendulum PUBLIC "C:/ProgramFiles/mingw-w64
                        /x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/lib")

target_link_libraries(double_pendulum sfml-graphics sfml-system sfml-window
        sfml-main)