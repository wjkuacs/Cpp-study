这篇文章意在使用 `c++` 来实现数据的分析和可视化，很显然这看着听鸡肋的，毕竟现在已经有了很多的语言，如 `Python` , `Matlab` ，但是我认为学习使用 `c++` 来进行数据分析与可视化也是对我的一种锻炼，下面我将开始。

```
使用操作系统：Ubuntu24.04
cmake 版本: 3.28.3
g++ 版本：13.3.0
可视化工具：CERN ROOT
CERN ROOT 版本： 6.34.02 
```
---
非常激动的准备开始写这篇文章，捣腾了一下午，终于成功了，这里关于 `CERN ROOT` 的安装我就不多赘述了，可能会在发一篇文章来讲，但是大概率不会。

# `C++` 代码演示
首先申明一下，这段代码是我直接ai生成出来的。

```c++
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
}#include "TCanvas.h"
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
```
可以看到，这段代码使用到了三个头文件，分别是 `TCanvas.h`，`TF1.h`，`TApplication.h`，这三个头文件分别是 `CERN ROOT` 中的三个类库，分别是画布，函数，应用程序。

事实上，在 `CERN ROOT` 当中，我们还可以看到很多这样的类库，包括 `TTree.h` , `TFile.h` , `TMinuit.h` 等等，这些都使得我们使用 `C++` 来进行数据的分析和可视化变得更加方便。接下来，我将开始讲解这些库的使用。

# `CMake` 的配置
`CMake` 的配置可以说是至关重要的，因为我们多数情况下将会之用 `CMakeLists.txt` 来进行我们的 `C++` 文件的编译、运行，，而我也是在这个地方捣腾了很久，目前给出一个比较成功的 `CMakeLists.txt` 文件。


```Cmake
cmake_minimum_required(VERSION 3.28.3)
project(DataVisualization)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置ROOT目录
set(ROOT_DIR "/home/ubuntu24/document/root")
list(APPEND CMAKE_PREFIX_PATH ${ROOT_DIR})

# 设置Minuit2头文件路径
include_directories(${ROOT_DIR}/include/Minuit2)

# 设置TBB库的完整路径
set(TBB_LIB "/usr/lib/x86_64-linux-gnu/libtbb.so.12")

# 查找ROOT包
find_package(ROOT REQUIRED)

# 包含ROOT的头文件
include(${ROOT_USE_FILE})

# 添加可执行文件
add_executable(usingTMinuit usingTMinuit.cpp)
add_executable(DataVisualization DataVisualization.cpp)


# 链接ROOT库和TBB库
target_link_libraries(usingTMinuit ${ROOT_LIBRARIES} Minuit ${TBB_LIB})
target_link_libraries(DataVisualization ${ROOT_LIBRARIES} ${TBB_LIB})
```

在这里面，首先是前面的两行
```cmake
cmake_minimum_required(VERSION 3.28.3)
project(DataVisualization)
```

第一行为 `CMake` 的最低版本要求；

第二行为项目名称，这里我们可以随意设置，在这里我设置成了我自己的文件夹名 `DataVisualization`；

接下来是设置 `C++` 的标准，这里我设置成了 `C++20`,而第二句则是为了确保必须使用这个标准；
```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

然后是设置 `ROOT` 的目录，这里我设置成了我自己的 `ROOT` 目录，这里我设置成了我自己的文件夹名 `root`,同时，我还将该路径添加到 `CMAKE_PREFIX_PATH` 中，以便 `CMake` 能够找到 `ROOT` 库；
```cmake
set(ROOT_DIR "/home/ubuntu24/document/root")
list(APPEND CMAKE_PREFIX_PATH ${ROOT_DIR})
```

之后，我们链接了另外一个库，即 `TBB` 库，可能有很多的读者还没有安装，可以通过命令
```shell
sudo apt-get install libtbb-dev
```
来安装，安装完成后，我们可以通过命令
```shell
find / -name libtbb.so.12
```
来找到 `TBB` 库的位置，我的电脑当中这个库在 `/usr/lib/x86_64-linux-gnu/libtbb.so.12`，将其赋值给 `TBB_LIB` 变量（在接下来我们提到的时候就可以少些很多的内容）；


来找到 `TBB` 库的位置，这里我找到了 `6_64-linux-gnu/libtbb.so.12`，将其赋值给 `TBB_LIB` 变量；
```cmake
set(TBB_LIB "/usr/lib/x86_64-linux-gnu/libtbb.so.12")
```

需要提到的是，这里的 `TBB` 库，其实我也不是非常的清楚，系统当时不停地给我报错，让我将其安装并链接，但是我又不知道为什么，所以这里我就直接将其链接了，希望有知道的读者可以告诉我。

这个是报错信息


```shell
/usr/bin/ld: 找不到 -ltbb: 没有那个文件或目录
collect2: error: ld returned 1 exit status
make[2]: *** [CMakeFiles/main.dir/build.make:116：main] 错误 1
make[1]: *** [CMakeFiles/Makefile2:83：CMakeFiles/main.dir/all] 错误 2
make: *** [Makefile:91：all] 错误 2
```

至关重要的还有添加可执行文件，主要的操作是


```cmake
add_executable(usingTMinuit usingTMinuit.cpp)
add_executable(DataVisualization DataVisualization.cpp)
```


这里的 `DataVisualization` 是可执行文件的名称，`DataVisualization.cpp` 是可执行文件的源文件。
最后，我们链接 `ROOT` 库和 `TBB` 库，这里的操作是


```cmake
target_link_libraries(usingTMinuit ${ROOT_LIBRARIES} Minuit ${TBB_LIB})
target_link_libraries(DataVisualization ${ROOT_LIBRARIES} ${TBB_LIB})
```


这里的 `DataVisualization` 和 `usingTMinuit` 是可执行文件的名称，`${ROOT_LIBRARIES}` 是 `ROOT` 库的名称，`${TBB_LIB}` 是 `TBB` 库的名称，同时由于我们的 `usingTMnuit.cpp` 文件当中需要引用到 `TMniuit.h` 这个库函数，因此我们还需要多添加一项 `Minuit` ，注意这里的是 `Minuit` ,而不是 `TMinuit` 亦或是 `Minuit2` ，这需要非常注意，否则在 `make` 的时候将会疯狂报错。


# `CERN ROOT` 众多类库的简单介绍
一般来说，我主要使用的库有 `TTree.h`, `TFile.h`, `TMinuit.h` ，`TCanvas.h`, `TF1.h`, `TApplication.h` ,接下来我简单介绍一下都有哪些语法。

## `TMinuit.h`
`TMinuit.h` 是 `CERN ROOT` 中的一个类库，它是一个 `C++` 实现的最小二乘拟合库，它可以用来拟合数据，拟合函数，拟合参数等等。


给出一个示例代码，我们将结合其来进行讲解。
```c++
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
```

接下来讲一讲 `TMinuit` 这个类及其其中的函数：
1. `minuit` ： `TMinuit` 类，创造出一个对象，我们利用 `minuit()`其来定义我们所需要的拟合参数的个数，示例当中则是 `minuit(2)`，这里表示定义了两个参数。
2. `DefineParameter` 其作用在于定义参数， `minuit.DefineParameter(0, "a", 1.0, 0.1, -10, 10);` 括号内的内容以此为：参数编号为 $0$,名称为 $a$,初始值为 $1.0$,参数的初始误差为 $0.1$,参数的下限值为 $-10$,上限值为 $10$；
3. `GetParameter` 其作用在于获取拟合参数的结果，`minuit.GetParameter(0, a, aErr);`依次为：参数编号 $0$,用于存储参数值的变量 $a$,剩下一个为存储参数误差的参数。
4. `SetFCN` 其作用在于设置拟合函数，`minuit.SetFCN(fcn);` 括号内的内容为拟合函数的名称，我们在示例当中在 `main` 函数之外定义了一个函数 `fcn`，其作用在于定义我们所需要拟合的函数。
5. 在这个 `fcn` 函数当中，也有很多的参数，`fcn(int &npar, double *gin, double &f, double *par, int iflag)`这其中，第一位 `int &npar` 示当前拟合中使用的参数个数，这个值由 `TMinuit` 自动传入，通常不需要手动修改，第二位 `double *gin` 这是一个指向数组的指针，用于存储梯度信息,第三位 `double &f` 用于存储目标函数的值，示例中使用的是最小二乘拟合，因此 `f` 通常是残差的平方和,第四位 `int iflag` 用于表示调用 `TMinuit` 的目的，若为 `1` 则是初始化调用，通常不需要特殊处理；若为 `2`,则是计算梯度的调用，需要填充 `gin` 数组；若为 `3`，则正常调用，计算目标函数的值，这里我们默认是 `3`。
6. `Migrad` 其作用在于执行拟合，`minuit.Migrad();` 括号内的内容为空。


以上便是 `TMinuit` 这个类库的简单介绍。

---

今天就到这儿吧，剩下的库之后再作介绍，希望各位读者大佬可以提一些建议，指导以下在下。
