#include "TCanvas.h"
#include "TF1.h"
#include "TApplication.h"

int main(int argc, char **argv) {
    // 创建ROOT应用程序
    TApplication app("ROOT Application", &argc, argv);

    // 创建画布
    TCanvas *c1 = new TCanvas("c1", "Function Plot", 800, 600);

    // 定义要绘制的函数
    // 这里我们绘制一个正弦函数，范围从0到10
    TF1 *f1 = new TF1("f1", "sin(x)", 0, 10);
    
    // 设置函数属性
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);
    f1->SetTitle("Sine Function;x;sin(x)");

    // 绘制函数
    f1->Draw();

    // 运行应用程序
    app.Run();

    // 清理
    delete c1;
    delete f1;

    return 0;
}