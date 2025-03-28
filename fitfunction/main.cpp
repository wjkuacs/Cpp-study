# include "fitfunction.h"
# include "readdata.h"

int main() {
    // 读取并分割数据
    auto allData = readDataFromFile("data.txt");
    auto [x_data, y_data] = splitData(allData);

    // 创建拟合器并输出结果
    LeastSquaresFitter fitter(x_data, y_data);
    std::cout << "Slope: " << fitter.getSlope() << std::endl;
    std::cout << "Intercept: " << fitter.getIntercept() << std::endl;
    std::cout << "Prediction for x=6: " << fitter.predict(6) << std::endl;

    return 0;
}