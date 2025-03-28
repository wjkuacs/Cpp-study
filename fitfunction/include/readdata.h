# pragma once

#ifndef READDATA_H
#define READDATA_H

#include <vector>
#include <string>
#include <utility>  // 添加pair的支持

std::vector<double> readDataFromFile(const std::string& filename);


std::pair<std::vector<double>, std::vector<double>> splitData(const std::vector<double>& allData);

#endif // READDATA_H