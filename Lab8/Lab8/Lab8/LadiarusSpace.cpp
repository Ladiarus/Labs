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

void input(double& x, double a, double b)
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
	while (true)
    {
        bool is_ok = true;
        cin >> s;
        for(auto c : exclude)
        {
            if (s.find(c) != -1)
                is_ok = false;
        }
        if (cin.fail() || (cin.peek() != '\n') || !is_ok)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод, нельзя использовать символы: \""<< exclude << "\"" << endl;
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
    int min_length_ind = -1;
    bool is_out_null = true;

    s += delim;
    for (char i : s)
    {
        if (i != delim)
        {
            if (is_out_null)
            {
                is_out_null = false;
            }

            out += i;

        }
        else if (!is_out_null)
        {
            v.push_back(out);
            out = "";
            is_out_null = true;
        }
    }
    return v;
}
int clamp(int n, int lower, int upper) {
    return max(lower, min(n, upper));
}