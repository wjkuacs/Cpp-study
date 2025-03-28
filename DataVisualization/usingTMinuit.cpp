#include "TMinuit.h"
#include <iostream>

// 定义拟合函数
void fcn(int &npar, double *gin, double &f, double *par, int iflag) {
    double x = 1.0; // 示例数据点
    double y = 2.0; // 示例数据点
    double model = par[0] * x + par[1]; // 线性模型
    f = (y - model) * (y - model); // 目标函数（最小二乘）
}

int main() {
    // 创建 TMinuit 对象
    TMinuit minuit(2);

    // 定义参数
    minuit.DefineParameter(0, "a", 1.0, 0.1, -10, 10); // 参数 a
    minuit.DefineParameter(1, "b", 1.0, 0.1, -10, 10); // 参数 b

    // 设置拟合函数
    minuit.SetFCN(fcn);

    // 执行拟合
    minuit.Migrad();

    // 获取拟合结果
    double a, aErr, b, bErr;
    minuit.GetParameter(0, a, aErr);
    minuit.GetParameter(1, b, bErr);

    // 打印结果
    std::cout << "a = " << a << " ± " << aErr << std::endl;
    std::cout << "b = " << b << " ± " << bErr << std::endl;

    return 0;
}