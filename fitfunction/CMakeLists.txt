cmake_minimum_required(VERSION 3.28.3)

project(FITFUNCTION)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# 包含头文件目录
include_directories(include)
#include_directories(/home/ubuntu24/document/root/include)

add_executable(main_camke main.cpp src/fitfunction.cpp src/readdata.cpp)

#target_link_libraries(main_camke Minuit::Minuit)