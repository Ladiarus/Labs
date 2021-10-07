#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <utility>
#include <vector>
#include <windows.h>
using namespace std;
int n;
int m, max_width;
double** arr;
double maxV;
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
void printArr()
{
    cout << "Матрица:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(max_width) <<arr[i][j] << " ";
        }
        cout << endl;
    }
}
void deleteStrCol(int x, int y) 
{

    for (int i = x; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = y; j < n-1; j++)
        {
            arr[i][j] = arr[i][j + 1];
        }
    }
    n--;

}
void findMaxAbs()
{
    vector<pair<int, int>> ret;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (abs(maxV) < arr[i][j])
            {
                maxV = arr[i][j];
            }
        }
    }
    
}
pair<int, int> findNextMaxAbs()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (abs(maxV) - abs(arr[i][j]) < 1e-7)
            {
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1);
}
void findMaxWidth()
{
    max_width = 2;
    int x = maxV;
    while (x > 10)
    {
        x /= 10;
        max_width++;
    }
}
int main(int argc, char* argv[])
{
    bool choice;
    setlocale(LC_ALL, "Russian");
    cout << "Введите размер матрицы\n";
    input(n, 1, INT_MAX);

    arr = new double* [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new double[n];
    }

    cout << "Желаете вводить элементы массива вручную? y/n\n";
    input(choice);
    if (choice)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                input(arr[i][j]);
            }
        }
    }
    else
    {
        long long random_min, random_max;
        srand(time(0));
        cout << "Введите минимальное случайное значение\n";
        input(random_min);
        cout << "Введите максимальное случайное значение\n";
        input(random_max);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                arr[i][j] = (rand() % (random_max - random_min + 1) + random_min);
            }
        }
        findMaxAbs();
        findMaxWidth();
        printArr();
    }
    findMaxAbs();
    findMaxWidth();
    cout << "Максимальное значение: " << maxV << endl;
    pair<int, int> p;
    p = findNextMaxAbs();
    while (p.first != -1)
    {
        deleteStrCol(p.first, p.second);
        p = findNextMaxAbs();
    }
    printArr();

    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    system("pause");
}