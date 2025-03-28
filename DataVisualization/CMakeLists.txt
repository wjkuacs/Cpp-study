cmake_minimum_required(VERSION 3.28.3)
project(DataVisualization)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 CUDA 架构
set(CMAKE_CUDA_ARCHITECTURES 86 75)  # 支持 Ampere (86) 和 Turing (75)

# 设置 ROOT 目录
set(ROOT_DIR "/home/ubuntu24/document/root")
list(APPEND CMAKE_PREFIX_PATH ${ROOT_DIR})



# 设置 Minuit2 头文件路径
include_directories(${ROOT_DIR}/include/Minuit2)

# 设置 MATH 头文件路径
include_directories(${ROOT_DIR}/include/Math)



# 设置 TBB 库的完整路径
set(TBB_LIB "/usr/lib/x86_64-linux-gnu/libtbb.so.12")

# 查找 ROOT 包
find_package(ROOT REQUIRED)

# 包含 ROOT 的头文件
include(${ROOT_USE_FILE})

# 添加可执行文件
add_executable(usingTMinuit usingTMinuit.cpp)
add_executable(DataVisualization DataVisualization.cpp)
add_executable(usingTF1TCanvasMath usingTF1TCanvasMath.cpp)

# 链接 ROOT 库和 TBB 库
target_link_libraries(usingTMinuit ${ROOT_LIBRARIES} Minuit ${TBB_LIB})
target_link_libraries(DataVisualization ${ROOT_LIBRARIES} ${TBB_LIB})
target_link_libraries(usingTF1TCanvasMath ${ROOT_LIBRARIES} ${TBB_LIB})