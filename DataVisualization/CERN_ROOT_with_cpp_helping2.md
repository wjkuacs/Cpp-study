接着之前的一篇文章，今天我们继续来讲解基于 `CERN ROOT` 的 `C++` 数据可视化。


# `CERN ROOT` 的一些包

## `TApplication.h` 类库

这样一类库其实还是比较重要的，就我最近的实践以来，貌似我要是想画图，那么我就必须要使用这个类库，并且是在 `main` 函数最开始的时候我就要去创建一个 `ROOT` 应用程序对象，即
```cpp
// 创建ROOT应用程序
    TApplication app("ROOT Application", &argc, argv);
```

并在代码的结尾之前（或者是你希望的地方，但是至少要有），写上一句
```cpp
    app.Run();
```
这样的话，我们就可以在 `C++` 当中使用 `ROOT` 来进行数据可视化了。
## `TF1.h` 和 `TCanvas.h` 类库 
这两个库一般来说是搭配来使用的。

1. `TF1.h` 是 `CERN ROOT` 当中用于定义和操作一维函数的类库，可以利用其来定义数学函数并对其进行积分、求导等操作。
2. `TCanvas.h` 是 `CERN ROOT` 当中用于创建和管理绘图窗口的类库，可以利用其来创建绘图窗口并将 `TF1` 对象绘制在其中。

接下来是代码演示：
```cpp
#include <iostream>
#include "TF1.h"
#include "TCanvas.h"
#include "TApplication.h"

int main(int argc, char **argv) {
    // 创建ROOT应用程序
    TApplication app("ROOT Application", &argc, argv);
    // 定义 x * e^x 函数
    TF1 *f1 = new TF1("f1", "x * exp(x)", -5, 5);
    
    // 绘制部分
    std::cout << "开始绘制 x * e^x 函数图像..." << std::endl;
    // 创建画布
    TCanvas *c1 = new TCanvas("c1", "Function Plot", 800, 600);
    // 设置函数颜色和宽度
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);
    // 设置坐标轴标题
    f1->SetTitle("x * e^x;x;y");
    f1->Draw();
    
    // 计算函数在 x = 5 处的值
    double value = f1->Eval(5);
    std::cout << "Function value at x = 5: " << value << std::endl;

    // 计算积分
    double integral = f1->Integral(0, 1);
    std::cout << "\n计算 x * e^x 在 [0,1] 区间上的积分值: " << integral << std::endl;
    
    // 运行应用程序
    app.Run();

    // 清理
    delete c1;
    delete f1;

    return 0;
}
```

看得出来，我们的 `TE1.h` 当中已经帮我们写好了很多个函数，比如 `Eval` ,`Intergral` 等等，我们可以直接调用,至于调用方法，在示例当中已经给出了。

```cpp
    double value = f1->Eval(5);
    double integral = f1->Integral(0, 1);
```

当然，我们也完全可以不用去以来这些已经写好了的函数，我们也可以凭借自己的智慧，使用上很多更新的算法来进行计算，这也是我在之后要做的，写出一个精度高的速度快的积分方法类。

而我们的 `TCanvas.h` 类库的使用方法也很明确了。

在画图前，我们需要的是创建一个画布
```cpp
    // 创建画布
    TCanvas *c1 = new TCanvas("c1", "Function Plot", 800, 600);
```
然后我们就可以在这个画布上进行画图了，与 `Python` ,`Matlab` 等语言一样，我们可以自由的设置函数的线条类型，颜色，宽度，以及图片的标题，横纵坐标。
```cpp
    // 设置函数颜色和宽度
    f1->SetLineColor(kBlue);
    f1->SetLineWidth(2);
    // 设置坐标轴标题
    f1->SetTitle("x * e^x;x;y");
    f1->Draw();
```

他也可以用来绘制对数坐标图（这在我们未来的研究当中也是非常常用的）
```cpp
    // 设置对数坐标
    c1->SetLogx();  // 设置x轴为对数刻度
    c1->SetLogy();  // 设置y轴为对数刻度
```

当然对于极坐标系这种，我们还需要额外配合 `TPad.h` 和 `TPolarGraph.h` 这两个类库来使用,在这里不过多的讲解。

