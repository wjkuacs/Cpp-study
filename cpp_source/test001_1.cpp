#include <bits/stdc++.h>
using namespace std;

// 计算 n! 的函数
int factorial(int n) {
    int result = 1;
    for (int j = 1; j <= n; j++) {
        result *= j;
    }
    return result;
}

int main() {
    int i = 0, sum = 0, n;
    cout << "请输入一个非负整数 n: ";
    cin >> n;

    // 检查 n 的合法性
    if (n < 0) {
        cout << "请输入非负整数！" << endl;
        return 1;
    }

    // 计算从 0! 到 n! 的累加和
    for (i = 0; i <= n; i++) {
        sum += factorial(i);
    }

    cout << "从 0! 到 " << n << "! 的累加和为: " << sum << endl;
    system("pause");
    return 0;
}
