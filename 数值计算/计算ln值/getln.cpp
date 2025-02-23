#include <bits/stdc++.h>

double _getLn(double x){
    //利用 ln(1 + x) - ln(1 - x) 迭代，由 (1 + x)/(1 - x) 求出底数
    double base = 1 - 2 *1.0/(1 + x);
    double answer = 0;
    int n = 0;
    while(1)
    {
        double _x = pow(base,2 * n + 1)/(2 * n + 1);
        answer += _x;
        ++n;
        if (fabs(_x) <= 0.0000000000000000001){
            return 2 * answer;
        }
    }
}

double getLn(double x) // 计算lnx
{
    if (x < 1) //将其写为科学技术法形式：0.0012 = 1.2e-3；
    {
        int _count = 0;
        do
        {
            x *= 10;
            ++_count;
        }while(x < 1);
        return _getLn(x) + _count * _getLn(10);
    }
    else
    {
        if (x <= 10){
            return _getLn(x);
        }
        else{
            // 将x拆分成科学技术法形式： ln23 = ln2.3 + ln10
            int _count = 0;
            do
            {
                x /= 10;
                ++_count;   
            } while (x>= 0);
            
            return _getLn(x) + _count * _getLn(10);
        }
    }
}

int main(){
    double x = 2.3;
    double res = getLn(x);
    std::cout << "ln(" << x << ") = " << res << std::endl;
    return 0;
}