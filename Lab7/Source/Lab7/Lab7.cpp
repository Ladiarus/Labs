#include <iostream>
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
int myLength(char* s);
vector<pair<char*, int>> splitFindMinLenStr(char* s, char delim, int& minLength)
{
    vector<pair<char*, int>> v;
    int currStrInd=0, sLen = myLength(s);
    s[sLen] = ' ';
    s[sLen + 1] = '\0';
    sLen++;
    int minLengthInd = -1, outLen=0;
    minLength = myLength(s);
    bool isOutNull = true;


    for (int i = 0; i < sLen; i++)
    {
        if (s[i] != delim)
        {
            if (isOutNull)
            {
                currStrInd = i;
                isOutNull = false;
            }
            outLen++;

        }
        else if (!isOutNull)
        {
            if (minLength >= outLen)
            {
                minLength = outLen;
            }
            char* out = new char[outLen + 5];
            for(int j = 0; j < outLen; j++)
            {
                out[j] = s[j + currStrInd];
            }
            out[outLen] = '\0';
            v.push_back(make_pair(out, currStrInd));
            outLen = 0;
            isOutNull = true;
        }
    }
    return v;
}
int myLength(char* s)
{
    int i = 0;
	while(s[i] != '\0')
	{
        i++;
	}
    return i;
}
int myFind(char* s, char c)
{
    int i = 0;
	while(s[i]!='\0')
	{
        if (s[i] == c)
            return i;
        i++;
	}
    return -1;
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    char s[255];
    int prewInd = 0, minLength;

    cout << "Введите строку\n";
    while (true)
    {
        cin.getline(s, 255);
        if (myFind(s, '\t') == -1)
            break;
        cout << "Неверный ввод\n";
    }

    vector<pair<char*, int>> v = splitFindMinLenStr(s, ' ', minLength);
    bool isFirstStr = true;
    for (auto p : v)
    {
        if (myLength(p.first) == minLength)
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
        if (myLength(p.first) == minLength)
        {
            cout << "\nСтрока с минимальной длиной: " << p.first << endl;
            cout << "Порядковый номер этой строки: " << p.second + 1 << endl;
            cout << "Длинa этой строки: " << minLength << endl;
        }
    }

    system("pause");
}