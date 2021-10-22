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

string centerString(const string& s, int width, char fill_with)
{
    string ret_str;
    int x = (width - s.length())/2;
    for (int i = 0; i < x; i++)
    {
        ret_str += fill_with;
    }
    ret_str += s;
    for (int i = ret_str.length() - 1; i < width; i++)
    {
        ret_str += fill_with;
    }
    return ret_str;
}

template <typename T>
void myQSort(vector<T>& v, int beg, int end, bool(*comp)(T*, T*))
{
    int curr_main_idx = end;
    if (end - beg == 2)
    {
        if (comp(&(v[beg]), &(v[end])))
        {
            swap(v[beg], v[end]);
        }
        return;
    }
    int i = beg;
    while (i < end)
    {
        if (comp(&v[i], &v[end]))
        {
            swap(v[i], v[curr_main_idx - 1]);
            swap(v[curr_main_idx - 1], v[curr_main_idx]);
            curr_main_idx--;
        }
        else
        {
            i++;
        }
    }
    myQSort(v, beg, curr_main_idx - 1, comp);
    myQSort(v, curr_main_idx + 1, end, comp);
}
