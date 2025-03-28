#include "TCanvas.h"
#include "TF1.h"
#include "TApplication.h"

int main(int argc, char **argv) {
    // 创建ROOT应用程序
    TApplication app("ROOT Application", &argc, argv);

    // 创建画布
    TCanvas *c1 = new TCanvas("c1", "Function Plot", 800, 600);

    // 定义第一个函数：正弦函数
    TF1 *f1 = new TF1("f1", "sin(x)", 0, 10);
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);
    f1->SetTitle("Sine Function;x;sin(x)");

    // 定义第二个函数：余弦函数
    TF1 *f2 = new TF1("f2", "cos(x)", 0, 10);
    f2->SetLineColor(kRed);
    f2->SetLineWidth(2);

    // 定义第三个函数：二次函数
    TF1 *f3 = new TF1("f3", "x*x", 0, 10);
    f3->SetLineColor(kGreen);
    f3->SetLineWidth(2);

    // 绘制第一个函数
    f1->Draw();

    // 绘制第二个函数（在同一画布上）
    f2->Draw("same");

    // 绘制第三个函数（在同一画布上）
    f3->Draw("same");

    // 运行应用程序
    app.Run();

    // 清理
    delete c1;
    delete f1;
    delete f2;
    delete f3;

    return 0;
}