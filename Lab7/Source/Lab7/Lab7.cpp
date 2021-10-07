﻿#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <iomanip>
#include <vector>
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
vector<pair<string, int>> splitFindMinLenStr(string s, char delim, int& minLength)
{
    string out, minLenStr;
    vector<pair<string, int>> v;
    int minLengthInd = -1;
    minLength = s.length();
    int currStrInd;
    bool isOutNull = true;

    s += ' ';
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != delim)
        {
            if (isOutNull)
            {
                currStrInd = i;
                isOutNull = false;
            }

            out += s[i];

        }
        else if (!isOutNull)
        {
            if (minLength >= out.length())
            {
                minLength = out.length();
            }
            v.push_back(make_pair(out, currStrInd));
            out = "";
            isOutNull = true;
        }
    }
    return v;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    string s;
    int prewInd = 0, minLength;
    cout << "Введите строку\n";
    while (true)
    {
        getline(cin, s);
        if (s.find('\t') == -1)
            break;
        cout << "Неверный ввод\n";
    }

    vector<pair<string, int>> v = splitFindMinLenStr(s, ' ', minLength);
    bool isFirstStr = true;
    for (auto p : v)
    {
        if (p.first.length() == minLength)
        {
            if (isFirstStr)
            {
                cout << setw(p.second + 1) << "^";
                prewInd = p.second;
                isFirstStr = false;
            }
            else
            {
                cout << setw(p.second - prewInd) << "^";
                prewInd = p.second;
            }
        }
    }

    for (auto p : v)
    {
        if (p.first.length() == minLength)
        {
            cout << "\nСтрока с минимальной длиной: " << p.first << endl;
            cout << "Порядковый номер этой строки: " << p.second + 1 << endl;
            cout << "Длинa этой строки: " << minLength << endl;
        }
    }

    system("pause");
}