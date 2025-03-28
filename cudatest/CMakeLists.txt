cmake_minimum_required(VERSION 3.28.3)

project(CudaTest LANGUAGES CXX CUDA)

set(CUDA_DIR "/usr/local/cuda-12.8")
list(APPEND CMAKE_PREFIX_PATH ${CUDA_DIR})

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CXX_STANDARD 20)

find_package(CUDA REQUIRED)

# 添加可执行文件
add_executable(cuda_test main.cu)

# 设置CUDA编译选项
set_property(TARGET cuda_test PROPERTY CUDA_SEPARABLE_COMPILATION ON)
set_property(TARGET cuda_test PROPERTY CUDA_ARCHITECTURES 86)  # 根据你的GPU架构调整

# 链接CUDA库
target_link_libraries(cuda_test PRIVATE CUDA::cudart)