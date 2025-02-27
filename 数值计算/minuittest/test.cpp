#include <iostream>
#include <TMinuit.h>

// 定义目标函数
void fcn(int& npar, double* deriv, double& f, double* param, int flag) {
    // 目标函数 f(x) = (x - 3)^2
    f = (param[0] - 3) * (param[0] - 3);
}

int main() {
    // 创建一个Minuit对象
    TMinuit minuit(1); // 1表示只有一个参数
    
    // 设置Minuit的目标函数
    minuit.SetFCN(fcn);
    
    // 定义初始猜测值，初始值为0
    double arglist[10];
    int ierflg = 0;
    minuit.mnparm(0, "x", 0.0, 1.0, -10.0, 10.0, ierflg); // 参数名字、初始值、步长、下限、上限、错误标志
    
    // 设置最小化方法
    arglist[0] = 5000;
    minuit.mnexcm("MIGRAD", arglist, 1, ierflg);
    
    // 打印最小化结果
    double parval, err;
    minuit.GetParameter(0, parval, err);
    std::cout << "最优参数值: " << parval << " +/- " << err << std::endl;
    
    return 0;
}