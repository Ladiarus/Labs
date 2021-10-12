#include "LadiarusSpace.h"
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
void input(string &s, string exclude)
{
    bool isOk;
    while (true)
    {
        isOk = true;
        cin >> s;
        for(auto c : exclude)
        {
            if (s.find(c) != -1)
                isOk = false;
        }
        if (cin.fail() || (cin.peek() != '\n') || !isOk)
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
vector<string> splitStr(string s, char delim)
{
    string out;
    vector<string> v;
    int minLengthInd = -1;
    bool isOutNull = true;

    s += delim;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != delim)
        {
            if (isOutNull)
            {
                isOutNull = false;
            }

            out += s[i];

        }
        else if (!isOutNull)
        {
            v.push_back(out);
            out = "";
            isOutNull = true;
        }
    }
    return v;
}