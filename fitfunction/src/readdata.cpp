#include "readdata.h"
#include <iostream>
#include <fstream>

std::vector<double> readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<double> data;
    double value;
    
    while (file >> value) {
        data.push_back(value);
        std::cout << "Read value: " << value << std::endl;  // 添加调试输出
    }
    return data;
}

std::pair<std::vector<double>, std::vector<double>> splitData(const std::vector<double>& allData) {
    std::vector<double> x_data, y_data;
    for (size_t i = 0; i < allData.size(); ++i) {
        if (i % 2 == 0) {
            x_data.push_back(allData[i]);
        } else {
            y_data.push_back(allData[i]);
        }
    }
    return {x_data, y_data};
}