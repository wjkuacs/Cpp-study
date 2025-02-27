#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// 读取数据文件，将数据存入 x 和 f_x 向量
void readData(const string& filename, vector<double>& x, vector<double>& f_x) {
    ifstream file(filename);
    double xi, fxi;
    while (file >> xi >> fxi) {
        x.push_back(xi);
        f_x.push_back(fxi);
    }
}

// 梯形法计算积分
double trapezoidalRule(const vector<double>& x, const vector<double>& f_x) {
    int n = x.size() - 1;  // 数据点数 - 1
    double sum = 0.0;
    
    // 计算每个小区间的宽度
    double h = x[1] - x[0];
    
    // 边界项
    sum += f_x[0] + f_x[n];
    
    // 中间项
    for (int i = 1; i < n; ++i) {
        sum += 2 * f_x[i];
    }
    
    // 返回积分结果
    return (h / 2) * sum;
}

int main() {
    vector<double> x, f_x;
    
    // 从文件读取数据
    readData("/home/ubuntu24/workspace/cpp/数值计算/积分/data.txt", x, f_x);
    
    // 计算 x^2 * f(x)
    vector<double> x2_f_x(f_x.size());
    for (size_t i = 0; i < f_x.size(); ++i) {
        x2_f_x[i] = x[i] * x[i] * f_x[i];
    }
    
    // 使用梯形法计算定积分
    double integral = trapezoidalRule(x, x2_f_x);
    
    cout << "积分结果: " << integral << endl;
    
    return 0;
}
