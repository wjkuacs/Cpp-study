/*
这是一段用chatgpt生成的代码，我将以这个代码为例子，进行一下初步的学习。
这段代码主要是计算某一组数据的平均值，方差、标准差
*/
#include <iostream> // 提供输入输出功能
#include <vector> // 使用 std::vector 动态存储数据
#include <fstream> // 处理文件读写
#include <cmath> // 用于数学函数，例如平方根（std::sqrt）
#include <numeric> // 使用 std::accumulate
#include <cstdlib>

using namespace std; // 简化标准库名称的使用

// Function to calculate mean（计算平均值的函数）
double calculateMean(const vector<double>& data) 
{
    return accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Function to calculate variance（计算方差的函数）
double calculateVariance(const vector<double>& data, double mean)
{
    double variance = 0.0;
    for (double value : data) {
        variance += (value - mean) * (value - mean);
    }
    return variance / data.size();
}

// Function to calculate standard deviation（计算标准差的函数）
double calculateStandardDeviation(double variance) 
{
    return sqrt(variance);
}

int main() 
{
    vector<double> data;
    ifstream inputFile("D:\\Code\\cpp\\cpp_data_analysis\\data.txt");

    // Check if file opened successfully
    if (!inputFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Read data from file
    double value;
    while (inputFile >> value) {
        data.push_back(value);
    }

    // Close the file
    inputFile.close();

    // Check if data is not empty
    if (data.empty()) {
        cerr << "No data to analyze." << endl;
        return 1;
    }

    // Perform calculations
    double mean = calculateMean(data);
    double variance = calculateVariance(data, mean);
    double standardDeviation = calculateStandardDeviation(variance);

    // Output results
    cout << "数据点的个数： " << data.size() << endl;
    cout << "数据平均值：" << mean << endl;
    cout << "数据方差：" << variance << endl;
    cout << "数据标准差: " << standardDeviation << endl;

    system("pause");

    return 0;
}
