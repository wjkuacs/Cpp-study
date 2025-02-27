#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "TMinuit.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TSpline.h"

using namespace std;

// 前向声明 DataFitter 类
class DataFitter;

// 全局 DataFitter 指针
extern DataFitter* gDataFitter;

// 抽象基类，定义拟合方法的接口
class FittingMethod {
public:
    virtual double fitFunction(double x, const vector<double>& par) = 0;
    virtual string getFunctionExpression() = 0;
    virtual int getParameterCount() = 0;
    virtual ~FittingMethod() {}
};

// 三角函数拟合方法
class TrigFitting : public FittingMethod {
public:
    double fitFunction(double x, const vector<double>& par) override {
        return par[0] * sin(par[1] * x + par[2]);
    }
    string getFunctionExpression() override {
        return "[0] * sin([1] * x + [2])";
    }
    int getParameterCount() override {
        return 3;
    }
};

// 高斯函数拟合方法
class GaussianFitting : public FittingMethod {
public:
    double fitFunction(double x, const vector<double>& par) override {
        return par[0] * exp(-(x - par[1]) * (x - par[1]) / (2 * par[2] * par[2]));
    }
    string getFunctionExpression() override {
        return "[0] * exp(-(x - [1]) * (x - [1]) / (2 * [2] * [2]))";
    }
    int getParameterCount() override {
        return 3;
    }
};

// 多项式拟合方法
class PolynomialFitting : public FittingMethod {
private:
    int degree;
public:
    PolynomialFitting(int deg) : degree(deg) {}
    double fitFunction(double x, const vector<double>& par) override {
        double result = 0;
        for (int i = 0; i <= degree; ++i) {
            result += par[i] * pow(x, i);
        }
        return result;
    }
    string getFunctionExpression() override {
        string expr = "";
        for (int i = 0; i <= degree; ++i) {
            if (i > 0) expr += " + ";
            expr += "[" + to_string(i) + "] * x^" + to_string(i);
        }
        return expr;
    }
    int getParameterCount() override {
        return degree + 1;
    }
};

// 样条拟合方法
class SplineFitting : public FittingMethod {
public:
    double fitFunction(double x, const vector<double>& par) override {
        // 样条拟合这里不使用参数，需要单独处理
        return 0;
    }
    string getFunctionExpression() override {
        return "Spline fit";
    }
    int getParameterCount() override {
        return 0;
    }
};

class DataFitter {
private:
    vector<double> x;
    vector<double> f_x;
    TMinuit minuit;
    string dataFilePath;
    string outputFilePath;
    FittingMethod* fittingMethod;

    // 读取数据文件，将数据存入 x 和 f_x 向量
    void readData(const string& filename) {
        ifstream file(filename);
        double xi, fxi;
        while (file >> xi >> fxi) {
            x.push_back(xi);
            f_x.push_back(fxi);
        }
    }

    // Minuit 的拟合目标函数
    static void fcn(int& npar, double* gin, double& f, double* par, int iflag) {
        f = 0.0;
        for (size_t i = 0; i < gDataFitter->x.size(); ++i) {
            double diff = gDataFitter->f_x[i] - gDataFitter->fittingMethod->fitFunction(gDataFitter->x[i], vector<double>(par, par + npar));
            f += diff * diff;  // 最小二乘法
        }
    }

public:
    DataFitter(const string& dataFile, const string& outputFile, FittingMethod* method)
        : dataFilePath(dataFile), outputFilePath(outputFile), fittingMethod(method), minuit(method->getParameterCount()) {
        gDataFitter = this;
        minuit.SetFCN(fcn);
        // 不再需要 SetObjectFit
    }

    void performFit() {
        readData(dataFilePath);
    
        // 设置参数初始值和步长
        vector<double> par(fittingMethod->getParameterCount(), 1.0);
        vector<double> step(fittingMethod->getParameterCount(), 0.1);
        for (int i = 0; i < fittingMethod->getParameterCount(); ++i) {
            minuit.DefineParameter(i, ("par" + to_string(i)).c_str(), par[i], step[i], 0, 0);
        }
    
        // 执行拟合
        minuit.Migrad();
    
        // 获取拟合结果
        vector<double> fitParams(fittingMethod->getParameterCount());
        vector<double> fitParamErrors(fittingMethod->getParameterCount());
        for (int i = 0; i < fittingMethod->getParameterCount(); ++i) {
            minuit.GetParameter(i, fitParams[i], fitParamErrors[i]);
        }
    
        // 输出拟合结果
        cout << "拟合结果: f(x) = " << fittingMethod->getFunctionExpression() << endl;
        for (int i = 0; i < fittingMethod->getParameterCount(); ++i) {
            cout << "参数 " << i << ": " << fitParams[i] << " ± " << fitParamErrors[i] << endl;
        }
    
        // 创建 TGraph 对象
        TGraph* graph = new TGraph(x.size(), &x[0], &f_x[0]);
        graph->SetTitle(fittingMethod->getFunctionExpression().c_str()); // 设置标题为拟合函数表达式
        graph->SetMarkerStyle(20);
        graph->SetMarkerSize(1);
    
        // 创建拟合函数对象
        TF1* fitFunc = new TF1("fitFunc", fittingMethod->getFunctionExpression().c_str(), 0, 1);
        for (int i = 0; i < fittingMethod->getParameterCount(); ++i) {
            fitFunc->SetParameter(i, fitParams[i]);
        }
        fitFunc->SetLineColor(kRed);
    
        // 创建画布并绘制
        TCanvas* canvas = new TCanvas("canvas", "拟合结果", 800, 600);
        graph->Draw("AP");
        fitFunc->Draw("same");
    
        // 保存图片
        canvas->SaveAs(outputFilePath.c_str());
    }

    ~DataFitter() {
        delete fittingMethod;
    }
};

// 全局 DataFitter 指针定义
DataFitter* gDataFitter = nullptr;

int main() {
    // 选择拟合方法
    FittingMethod* method = new PolynomialFitting(9);  // 可以替换为 GaussianFitting, PolynomialFitting(2) ,TrigFitting等

    DataFitter fitter("/home/ubuntu24/workspace/cpp/数值计算/积分/data.txt", "/home/ubuntu24/workspace/cpp/数值计算/积分/fit_result.png", method);
    fitter.performFit();

    return 0;
}
