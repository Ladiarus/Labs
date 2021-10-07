#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>
using namespace std;
template <class T>
void input(T& a)
{
    while (true)
    {
        cin >> a;
        if (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ' && cin.peek() != '\t'))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод" << endl;
        }
        else
        {
            return;
        }
    }
}

double y_func(double x) 
{
    return (-log(sqrt(1 + x * x)) + x * atan(x));
}

int n;
double count_sum(double x)
{
    double sum = 0, prX, a=-1;
    for (long long k = 1; k <= n; k++)
    {
        prX = a;
        a = -prX * x * x;
        sum += a / ((2 * k)*(2 * k - 1));
    }
    return sum;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    
    double a, b, h, y, sum;
    cout << "Введите a\n";
    input(a);
    cout << "Введите b\n";
    input(b);
    cout << "Введите h\n";
    input(h);
    cout << "Введите n\n";
    input(n);
    cout << 
        "|———————————————|————————————————|————————————————————————|—————————————————————————|\n"
        "|       X       |      Y(X)      |          S(X)          |        Y(X)-S(X)        |\n"
        "|———————————————|————————————————|————————————————————————|—————————————————————————|\n";
    for (double x = a; x <= b; x += h)
    {
        cout << "|" << setw(15) << fixed << x << "|";
        y = y_func(x);
        cout << setw(16) << fixed << y << "|";
        sum = count_sum(x);
        cout << setw(24) << fixed << sum << "|";
        cout << setw(25) << fixed << abs(y - sum) << "|\n";
        cout << "|———————————————|————————————————|————————————————————————|—————————————————————————|\n";
    }
    system("pause");
}
