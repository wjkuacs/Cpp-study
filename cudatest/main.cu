#include <iostream>
#include <cuda_runtime.h>

// 定义向量长度
#define N 1024

// 定义一个 CUDA 内核函数：向量加法
__global__ void vectorAdd(const float* A, const float* B, float* C, int numElements)
{
    // 每个线程计算一个元素
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < numElements) {
        C[i] = A[i] + B[i];
    }
}

int main()
{
    // 主机端数据
    float h_A[N], h_B[N], h_C[N];
    
    // 初始化数据
    for (int i = 0; i < N; i++) {
        h_A[i] = static_cast<float>(i);
        h_B[i] = static_cast<float>(i * 2);
    }

    // 设备端数据
    float *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, N * sizeof(float));
    cudaMalloc((void**)&d_B, N * sizeof(float));
    cudaMalloc((void**)&d_C, N * sizeof(float));

    // 将数据复制到设备
    cudaMemcpy(d_A, h_A, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * sizeof(float), cudaMemcpyHostToDevice);

    // 启动CUDA内核
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // 将结果复制回主机
    cudaMemcpy(h_C, d_C, N * sizeof(float), cudaMemcpyDeviceToHost);

    // 验证结果
    bool success = true;
    for (int i = 0; i < N; i++) {
        if (fabs(h_C[i] - (h_A[i] + h_B[i])) > 1e-5) {
            success = false;
            break;
        }
    }

    if (success) {
        std::cout << "Vector addition successful!" << std::endl;
    } else {
        std::cout << "Vector addition failed!" << std::endl;
    }

    // 释放设备内存
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}