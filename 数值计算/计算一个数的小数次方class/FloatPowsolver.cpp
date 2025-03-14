#include <bits/stdc++.h>

class FloatPowSolver {
public:
    double solveFloatPow(long double a, long double b) {
        int sig = 1;
        if (b < 0) {
            sig = -1;
        }
        int _b = (int)fabs(b);
        long double bb = fabs(b) - _b;   // 将次方写成整数部分和小数部分，如 1.2 = 1 + 0.2
        
        long double answer1 = pow(a, _b);    // 计算出整数部分的次方
        long double base = bb * log(a);  // 将小数部分转换为对数，然后取指数

        long double answer = 1;

        int n = 1;
        long double _answer = 1.0;
        while (1)
        {
            _answer = _answer * (base / n);
            answer += _answer;
            if (fabs(_answer - 0) <= 0.000000000000000001)  // 设置精度，看个人了
            {
                break;
            }
            ++n;
            std::cout << "n:" << n << std::endl;
        }
        long double ans = answer1 * answer;
        if (sig == -1) {
            ans = 1 / ans;
        }
        return ans;
    }
};

int main() {
    FloatPowSolver solver;
    double a = 2.0, b = 1.2;
    double res = solver.solveFloatPow(a, b);
    std::cout << "result: " << res << std::endl;
    return 0;
}