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


double yFunc(double x)
{
    return (-log(sqrt(1 + x * x)) + x * atan(x));
}

int n;
double sumFunc(double x)
{
    double sum = 0, prX, a = -1;
    for (long long k = 1; k <= n; k++)
    {
        prX = a;
        a = -prX * x * x;
        sum += a / ((2 * k) * (2 * k - 1));
    }
    return sum;
}


double y_SFunc(double x)
{
    return abs(yFunc(x) - sumFunc(x));
}

void outRez(double (*func)(double), double a, double b, double h)
{
    
    for (double x = a; x <= b; x += h)
    {
        cout << "|" << setw(15) << fixed << x;
        cout << "|" << setw(16) << fixed << func(x) << "|\n";
    }
    cout<< "|--------------------------------|\n";
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
        "|--------------------------------|\n"
        "|       X       |      F(X)      |\n"
        "|--------------------------------|\n";
    cout << 
        "|          Function Y(X)         |\n"
        "|--------------------------------|\n";
    outRez(yFunc, a, b, h);

    cout <<
        "|          Function S(X)         |\n"
        "|--------------------------------|\n";
    outRez(sumFunc, a, b, h);

    cout <<
        "|       Function Y(X)-S(X)       |\n"
        "|--------------------------------|\n";
    outRez(y_SFunc, a, b, h);

    system("pause");
}
