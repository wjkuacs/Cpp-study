# include "fitfunction.h"


LeastSquaresFitter::LeastSquaresFitter(const std::vector<double>& x, const std::vector<double>& y)
    : x_data(x), y_data(y) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    int n = x_data.size();

    for (int i = 0; i < n; ++i) {
        sum_x += x_data[i];
        sum_y += y_data[i];
        sum_xy += x_data[i] * y_data[i];
        sum_x2 += x_data[i] * x_data[i];
    }

    slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    intercept = (sum_y - slope * sum_x) / n;
}

double LeastSquaresFitter::getSlope() const {
    return slope;
}

double LeastSquaresFitter::getIntercept() const {
    return intercept;
}

double LeastSquaresFitter::predict(double x) const {
    return slope * x + intercept;
}