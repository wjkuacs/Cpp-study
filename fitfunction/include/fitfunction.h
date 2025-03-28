# pragma once

#ifndef FITFUNCTION_H
#define FITFUNCTION_H


# include <iostream>
# include <cmath>
# include <fstream>
# include <vector>

class LeastSquaresFitter {
private:
    std::vector<double> x_data;
    std::vector<double> y_data;
    double slope;
    double intercept;

public:
    LeastSquaresFitter(const std::vector<double>& x, const std::vector<double>& y);
    double getSlope() const;
    double getIntercept() const;
    double predict(double x) const;
};

#endif // FITFUNCTION_H
