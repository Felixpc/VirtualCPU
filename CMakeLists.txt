cmake_minimum_required(VERSION 3.22)
project(VirtualCPU)

set(CMAKE_CXX_STANDARD 20)

add_executable(VirtualCPU main.cpp CPU/bus/Bus.h CPU/Register.h CPU/Clock.h CPU/Block.h CPU/ALU.h CPU/RAM.h CPU/PC.h)
