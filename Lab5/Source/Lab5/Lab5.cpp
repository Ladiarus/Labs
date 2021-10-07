#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>
using namespace std;
int n;

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
void input(int& x, int a, int b)
{
    while (true)
    {
        input(x);
        if (x < a || x > b)
        {
            cout <<
                "Неверный ввод\n"
                "Введите число на промежутке от " << a << " до " << b << endl;
        }
        else
            return;
    }
}
void input(bool& b)
{
    char c;
    while (true)
    {
        input(c);
        if (c != 'y' && c != 'n')
        {
            cout <<
                "Неверный ввод\n"
                "Введите y или n\n";
        }
        else
        {
            b = (c == 'y' ? true : false);
            return;
        }
    }
}
int findIndexOfMax(int* arr)
{
    int max = arr[0], ind_max = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
            ind_max = i;
        }
    }
    return ind_max;
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    int arr[10000];
    int index_max, sum = 0;
    bool choice;

    cout << "Введите количество элементов массива\n";
    input(n, 1, INT_MAX);

    cout << "Желаете вводить элементы массива вручную? y/n\n";
    input(choice);
    if (choice)
    {
        for (int i = 0; i < n; i++)
        {
            input(arr[i]);
        }
    }
    else
    {
        int random_min, random_max;
        srand(time(0));
        cout << "Введите минимальное случайное значение\n";
        input(random_min);
        cout << "Введите максимальное случайное значение\n";
        input(random_max);
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % (random_max - random_min + 1) + random_min;
        }
        cout << "Массив:\n";
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << endl;
        }
    }
    index_max = findIndexOfMax(arr);
    cout << "Максимальный элемент в массиве: " << arr[index_max] << endl;

    for (int i = 0; i < index_max; i++)
    {
        if (arr[i] > 0)
        {
            sum += arr[i];
        }
    }
    cout << "Сумма: " << sum << endl;
    system("pause");
}