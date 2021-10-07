#include <iostream>
#include <cmath>
using namespace std;
template <class T>
void input(T &a)
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
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    double a, d, z, x, func_res=0, y;
    int choise;
    cout << "Введите a" << endl;
    input(a);
    cout << "Введите d" << endl;
    input(d);
    cout << "Введите z" << endl;
    input(z);
    if (z > 0)
        x = -3 * z;
    else
        x = z * z;
    cout << "Значение x: " << x << endl;

    cout << "Выберите функцию:\n1 - 2*x\n2 - x^2\n3 - x/3\n";
    do
    {
        input(choise);
        switch (choise)
        {
        case 1:
            func_res = 2 * x;
            cout << "Выбрана функция 2*x\n";
            break;
        case 2:
            func_res = x * x;
            cout << "Выбрана функция x^2\n";
            break;
        case 3:
            func_res = x / 3;
            cout << "Выбрана функция x/3\n";
            break;
        default:
            cout << "Неверный ввод\n";
            continue;
        }
    } while (choise < 1 || choise > 3);
    cout << "Значение функции: " << func_res << endl;
    y = 2 * func_res * (a * sin(x) + d * exp(-(x + 3)));
    cout << "Результат : " << y <<endl;
    system("pause");
}