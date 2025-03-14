#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
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

// CUDA 版本的 fitFunction
__global__ void cudaFitFunction(double* x, double* result, const double* par, int n, int paramCount, int methodType) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        switch (methodType) {
            case 0:  // MLCombinationFitting
                result[idx] = par[0] * pow(x[idx], par[1]) + 
                            par[2] * sin(par[3] * x[idx] + par[4]) + 
                            par[5] * exp(par[6] * x[idx]);
                break;
            // 添加其他拟合方法的CUDA实现
            default:
                result[idx] = 0.0;
        }
    }
}

// 抽象基类，定义拟合方法的接口
class FittingMethod {
public:
    virtual double fitFunction(double x, const vector<double>& par) = 0;
    virtual string getFunctionExpression() = 0;
    virtual int getParameterCount() = 0;
    virtual int getMethodType() = 0;  // 新增方法，用于CUDA识别拟合方法类型
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
    int getMethodType() override {
        return 1;
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
    int getMethodType() override {
        return 2;
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
    int getMethodType() override {
        return 3;
    }
};

// 样条拟合方法
class SplineFitting : public FittingMethod {
public:
    double fitFunction(double x, const vector<double>& par) override {
        return 0;
    }
    string getFunctionExpression() override {
        return "Spline fit";
    }
    int getParameterCount() override {
        return 0;
    }
    int getMethodType() override {
        return 4;
    }
};

// 岭回归拟合方法
class RidgeFitting : public FittingMethod {
private:
    double lambda;
public:
    RidgeFitting(double l) : lambda(l) {}
    double fitFunction(double x, const vector<double>& par) override {
        double result = par[0];
        for (size_t i = 1; i < par.size(); ++i) {
            result += par[i] * pow(x, i);
        }
        return result;
    }
    string getFunctionExpression() override {
        return "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x + [6]*x*x*x*x*x*x + [7]*x*x*x*x*x*x*x + [8]*极x*x*x*x*x*x*x + [9]*x*x*x*x*x*x*x*x*x";
    }
    int getParameterCount() override {
        return 10;
    }
    double getLambda() const {
        return lambda;
    }
    int getMethodType() override {
        return 5;
    }
};

// 套索回归拟合方法
class LassoFitting : public FittingMethod {
private:
    double lambda;
public:
    LassoFitting(double l) : lambda(l) {}
    double fitFunction(double x, const vector<double>& par) override {
        double result = par[0];
        for (size_t i = 1; i < par.size(); ++i) {
            result += par[i] * pow(x, i);
        }
        return result;
    }
    string getFunctionExpression() override {
        return "[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x + [6]*x*x*x*x*x*x + [7]*x*x*x*x*x*x*x + [8]*x*x*x*x*x*x*x*x + [9]*x*x*x*x*x*x*x*x*x";
    }
    int getParameterCount() override {
        return 10;
    }
    double getLambda() const {
        return lambda;
    }
    int getMethodType() override {
        return 6;
    }
};

// 机器学习组合拟合方法
class MLCombinationFitting : public FittingMethod {
public:
    double fitFunction(double x, const vector<double>& par) override {
        return par[0] * pow(x, par[1]) + 
               par[2] * sin(par[3] * x + par[4]) + 
               par[5] * exp(par[6] * x);
    }
    string getFunctionExpression() override {
        return "[0] * x^[1] + [2] * sin([3] * x + [4]) + [5] * exp([6] * x)";
    }
    int getParameterCount() override {
        return 7;
    }
    int getMethodType() override {
        return 0;
    }
};

// 复杂组合拟合方法
class ComplexCombinationFitting : public FittingMethod {
public:
    double fitFunction(double x, const vector<double>& par) override {
        return par[0] * pow(x, par[1]) + 
               (par[2] * pow(x, par[3])) * sin(par[4] * pow(x, par[5]) + par[6]) + 
               (par[7] * pow(x, par[8]) + par[9]) * exp(par[10] * pow(x, par[11]));
    }
    string getFunctionExpression() override {
        return "[0]*x^[1] + ([2]*x^[3])*sin([4]*x^[5]+[6]) + ([7]*x^[8]+[9])*exp([10]*x^[11])";
    }
    int getParameterCount() override {
        return 12;
    }
    int getMethodType() override {
        return 7;
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

    // CUDA相关成员
    double* d_x;
    double* d_f_x;
    double* d_par;
    double* d_result;

    void allocateCudaMemory() {
        cudaMalloc((void**)&d_x, x.size() * sizeof(double));
        cudaMalloc((void**)&d_f_x, f_x.size() * sizeof(double));
        cudaMalloc((void**)&d_par, fittingMethod->getParameterCount() * sizeof(double));
        cudaMalloc((void**)&d_result, x.size() * sizeof(double));
    }

    void freeCudaMemory() {
        cudaFree(d_x);
        cudaFree(d_f_x);
        cudaFree(d_par);
        cudaFree(d_result);
    }

    // 读取数据文件
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
        // 将数据复制到设备端
        cudaMemcpy(gDataFitter->d_x, &gDataFitter->x[0], gDataFitter->x.size() * sizeof(double), cudaMemcpyHostToDevice);
        cudaMemcpy(gDataFitter->d_par, par, npar * sizeof(double), cudaMemcpyHostToDevice);

        // 设置CUDA网格和块大小
        int blockSize = 256;
        int gridSize = (gDataFitter->x.size() + blockSize - 1) / blockSize;

        // 调用CUDA核函数
        cudaFitFunction<<<gridSize, blockSize>>>(gDataFitter->d_x, gDataFitter->d_result, gDataFitter->d_par, 
                                               gDataFitter->x.size(), npar, gDataFitter->fittingMethod->getMethodType());

        // 将结果复制回主机
        vector<double> result(gDataFitter->x.size());
        cudaMemcpy(&result[0], gDataFitter->d_result, gDataFitter->x.size() * sizeof(double), cudaMemcpyDeviceToHost);

        // 计算残差平方和
        f = 0.0;
        for (size_t i = 0; i < gDataFitter->x.size(); ++i) {
            double diff = gDataFitter->f_x[i] - result[i];
            f += diff * diff;
        }

        // 如果是岭回归，添加 L2 正则化项
        if (auto ridge = dynamic_cast<RidgeFitting*>(gDataFitter->fittingMethod)) {
            double lambda = ridge->getLambda();
            for (int i = 0; i < npar; ++i) {
                f += lambda * par[i] * par[i];
            }
        }

        // 如果是套索回归，添加 L1 正则化项
        if (auto lasso = dynamic_cast<LassoFitting*>(gDataFitter->fittingMethod)) {
            double lambda = lasso->getLambda();
            for (int i = 0; i < npar; ++i) {
                f += lambda * abs(par[i]);
            }
        }
    }

public:
    DataFitter(const string& dataFile, const string& outputFile, FittingMethod* method)
        : dataFilePath(dataFile), outputFilePath(outputFile), fittingMethod(method), minuit(method->getParameterCount()) {
        gDataFitter = this;
        minuit.SetFCN(fcn);
        allocateCudaMemory();
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
        graph->SetTitle(fittingMethod->getFunctionExpression().c_str());
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
        freeCudaMemory();
        delete fittingMethod;
    }
};

// 全局 DataFitter 指针定义
DataFitter* gDataFitter = nullptr;

int main() {
    // 选择拟合方法
    FittingMethod* method = new MLCombinationFitting();

    DataFitter fitter("/home/ubuntu24/workspace/cpp/数值计算/积分/data.txt", "/home/ubuntu24/workspace/cpp/数值计算/积分/fit_result.png", method);
    fitter.performFit();

    return 0;
}