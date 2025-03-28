#include <iostream>
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "Math/Functor.h"
#include "Math/Integrator.h"

int main(int argc, char **argv) {
    // 创建ROOT应用程序
    TApplication app("ROOT Application", &argc, argv);
    // 定义 x * e^x 函数
    TF1 *f1 = new TF1("f1", "x * exp(x)", -5, 5);
    TF1 *f2 = new TF1("f2", "x * x", -5, 5);
    
    // 绘制部分
    // 创建画布
    TCanvas *c = new TCanvas("c", "Function Plot", 800, 600);
    // 设置函数颜色和宽度
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);
    f2->SetLineColor(kRed);
    f2->SetLineWidth(2);
    // 设置坐标轴标题
    f1->SetTitle("f(x);x;y");
    f1->Draw();
    f2->Draw("same");
    
    // 计算函数在 x = 5 处的值
    double value1 = f1->Eval(5);
    double value2 = f2->Eval(5);
    std::cout << "Function1 x * exp(x) value at x = 5: " << value1 << std::endl;
    std::cout << "Function2 x * x value at x = 5: " << value2 << std::endl;

    // 计算导数部分
    std::cout << "\n开始计算 x * e^x 的导数..." << std::endl;
    TF1 *df1 = new TF1("df1", "(1 + x) * exp(x)", -5, 5);
    std::cout << "x * e^x 的导数是 (1 + x) * e^x，已创建导数函数对象。" << std::endl;
    
    /*
    //计算不定积分（使用数学库计算不定积分）
    ROOT::Math::Functor1D func(*f2);
    ROOT::Math::Integrator integrator(func);
    double x = 2.0;  // 要计算的点
    double integral_value = integrator.IntegralUp(x);
    std::cout << "f2 不定积分在 x = " << x << " 处的值: " << integral_value << std::endl;
    */
   
    // 计算定积分
    double integral = f1->Integral(0, 1);
    std::cout << "\n计算 x * e^x 在 [0,1] 区间上的积分值: " << integral << std::endl;
    
    // 运行应用程序
    app.Run();

    // 清理
    delete c;
    delete f1;
    delete f2;

    return 0;
}