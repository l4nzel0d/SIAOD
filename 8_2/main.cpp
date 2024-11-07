#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int countSequences(int n) {
    if (n == 0) return 1;
    if (n == 1) return 2;
    
    int dp[n+1];
    dp[0] = 1;
    dp[1] = 2;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2]; 
    }

    return dp[n];
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int n;
    cout << "Введите длину последовательности n: ";
    cin >> n;

    int result = countSequences(n);
    cout << "Число последовательностей длины " << n << " без подряд идущих единиц: " << result << endl;

    cout << endl;
    cout << "Число переборов при динамическом программировании: " << n + 1 << endl;
    // Оценка числа переборов при стратегии "в лоб"
    cout << "Число переборов при стратегии \"в лоб\": " << pow(2, n) << endl;

    return 0;
}

