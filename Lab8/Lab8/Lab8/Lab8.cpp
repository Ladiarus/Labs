#include "Lab8.h"
#include "LadiarusSpace.h"
int n, amount_of_lines;
short current_pointer_y;
bool is_exit;
COORD curr_coord;
CONSOLE_SCREEN_BUFFER_INFO info;
string curr_in_file, curr_out_file;
vector <int> out_weigths{19, 5, 8, 5, 5, 5, 5, 7};
ifstream fin;
ofstream fout;
fstream create_stream;
HANDLE hCon;

void movePointer(short y)
{
    SetConsoleCursorPosition(hCon, {0, current_pointer_y});
    cout << ' ';
    current_pointer_y = y;
    SetConsoleCursorPosition(hCon, { 0, y });
    
    cout << "\033[0;32m#\033[0;m";
    SetConsoleCursorPosition(hCon, { 0, y });
    
}
void resetCursor()
{
    SetConsoleCursorPosition(hCon, { 0, current_pointer_y });
    cout << ' ';
    SetConsoleCursorPosition(hCon, { curr_coord });
}

void viewOptions()
{
    cout << "Create File - 1\nChoose File - 2\nAdd - 3\nChange - 4\n";
    chooseOption({createFileSelect, chooseFileSelect, addStringSelect, editStringSelect});
}
bool isFileExists(string s)
{
    create_stream.close();
    create_stream.open(s, ios::in);
    if (create_stream.is_open())
    {
        create_stream.close();
        return true;
    }
    else
    {
        create_stream.close();
        return false;
    }
}
void viewFile()
{
    system("cls");
    cout << " " << setfill('-') << setw(38) << curr_in_file;
    cout << setfill('-') << setw(39 - curr_in_file.length()) << "" << "\n"
        " |        Имя        | Год | Группа | Физ | Мат | Инф | Хим | Средн |\n"
		" |-------------------|-----|--------|-----|-----|-----|-----|-------|\n";
    cout.fill(' ');
    string s;
    fin.close();
    fin.open(curr_in_file);
    amount_of_lines = 0;
    while (!fin.eof())
    {
        getline(fin, s);
        vector <string>v = splitStr(s, ' ');
        if (v.size() == 9)
        {
            cout << " ";
            if (amount_of_lines % 2 != 0)
            {
                cout << "\033[48;5;235m";
            }
            cout << "|" << setw(out_weigths[0]) << v[0] + " " + v[1] << "|";

            for (int i = 2; i < v.size(); i++)
            {
                cout << setw(out_weigths[i - 1]) << v[i] << '|';
            }
            cout << ' ' << "\033[34m" << amount_of_lines + 1 << "\033[m" << endl ;
            
        }
        amount_of_lines++;
    }
    viewOptions();
}
void clearFileSelect()
{
    bool b;
    cout << "Вы точно хотите очистить этот файл? y/n\n";
    input(b);
    if (b)
        clearFile(curr_in_file);
}
void clearFile(string s)
{
    fin.close();
    fin.open(s, ios::trunc);
    fin.close();
    fin.open(s);
}
void createFileSelect()
{
    string s;
    cout << "Введите название файла, оканчивающееся на .txt\n";
    do {
        input(s, "/<>?|*:\"\\");
        if (s.substr(s.length() - 4, 4) != ".txt")
            cout << "Неверный ввод\n";
    } while (s.substr(s.length() - 4, 4) != ".txt");
    createFile(s);
}
void createFile(string s)
{
    if (isFileExists(s))
    {
        bool b;
        cout << "Файл существует, очистить его его? y/n\n";
        input(b);
        
        if (b)
            clearFile(s);
    }
    else
    {
        create_stream.open(s, ios::out);\
        create_stream.close();
    }

}
void chooseFileSelect()
{
    string s;
    cout << "Введите название файла, оканчивающееся на .txt\n";
    do {
        input(s, "/<>?|*:\"\\");
        
    } while (s.substr(s.length() - 4, 4) != ".txt");
    chooseFile(s);
}
void chooseFile(string s)
{
    if (isFileExists(s))
    {
        fin.close();
        fin.open(s);
        curr_in_file = s;
    }
    else
    {
        bool b;
        cout << "Файла не существует, создать его? y/n\n";
        input(b);
        if(b)
        {
            createFile(s);
        }
    }
}
void editStringSelect()
{
    int c = 0, x, y;
    cout << "Выберите строку, которую хотите изменить (Стрелка Вверх(Вниз), чтобы переместить указатель)\n";
    cout << "Или введите номер строки(нажмите ESC, чтобы выйти из режима указателя на строку)\n";
    GetConsoleScreenBufferInfo(hCon, &info);
    curr_coord = info.dwCursorPosition;
    while (true)
    {
        int c = _getch();
        if (c == 224) { // if the first value is esc

            switch (_getch())
        	{
            case KEY_UP:
                y = clamp(current_pointer_y - 1, 3, amount_of_lines + 2);
                movePointer(y);
                break;
            case KEY_DOWN:
                y = clamp(current_pointer_y + 1, 3, amount_of_lines + 2);
                movePointer(y);
                break;
            default:
                ; 
            }
        }
        else if(c == 13) //если нажат Enter
        {
            
        }
        else if (c == 27)
        {
	        
        }
        else
        {
            resetCursor();
            GetConsoleScreenBufferInfo(hCon, &info);
            curr_coord = info.dwCursorPosition;
            int a;
            cin >> a;

        }
    }
}

void chooseOption(vector<void(*)()> args)
{
    int choice;
    cout << "EXIT - 0\n";
    input(choice, 0, args.size());
    for (int i = 0; i < args.size(); i++)
    {
        if (i + 1 == choice)
            args[i]();
    }
    if(choice == 0)
    {
        is_exit = true;
    }
    
}

void addStringSelect()
{
    string s;
    vector <string> v;
    int sum = 0;
    StudentData *sd = new StudentData();
    bool is_valid = false;
    cout << "Введите фамилию и через пробел инициалы\n";
    cin.ignore(1000, '\n');
    while (!is_valid)
    {
        sum = 0;
        is_valid = true;
        
        getline(cin, s);

        v = splitStr(s, ' ');
        if(v.size()!=2)
        {
            is_valid = false;
            cout << "Неверный ввод\n";
            continue;
        }
        for(char c : s)
        {
            if (!(isalpha(c) || (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я')) && c != ' ' && c != '.')
            {
                is_valid = false;
                break;
            }
        }
        if(s.length()>19)
        {
            cout << "Максимальная длина " << out_weigths[0] << " символов\n";
            is_valid = false;
            continue;

        }
        if(!is_valid)
        {
            cout << "Неверный ввод\n";
        }
    }
    sd->name = s;
    cout << "Введите год рождения\n";
    input(sd->year, 1900, 2021);
    cout << "Введите номер группы\n";
    input(sd->number, 0, 100000000-1);
    cout << "Введите оценку по физике\n";
    input(sd->marks[0], 0, 10);
    cout << "Введите оценку по математике\n";
    input(sd->marks[1], 0, 10);
    cout << "Введите оценку по информатике\n";
    input(sd->marks[2], 0, 10);
    cout << "Введите оценку по химии\n";
    input(sd->marks[3], 0, 10);
    sd->average_mark = (sd->marks[0] + sd->marks[1] + sd->marks[2] + sd->marks[3]) / 4;
    addString(curr_in_file, sd);

}

void addString(string path, const StudentData* sd)
{
    fin.close();
    fout.close();
    fout.open(path, ios::app);
    fout << endl;
    fout << sd->name << ' ';
    fout << sd->year << ' ';
    fout << sd->number << ' ';
    fout << round(sd->marks[0] * 10) / 10 << ' ';
    fout << round(sd->marks[1] * 10) / 10 << ' ';
    fout << round(sd->marks[2] * 10) / 10 << ' ';
    fout << round(sd->marks[3] * 10) / 10 << ' ';
    fout << round(sd->average_mark * 10) / 10;
    fout.close();
    delete sd;
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Присваивание дескриптора консоли

    COORD  size{ 100, 30 };
    SetConsoleScreenBufferSize(hCon, size);//размер буфера
    
    fin.open("input.txt");
    curr_in_file = "input.txt";
    while (true)
    {
        viewFile();
        
        if(is_exit)
            break;
    }
    system("pause");
}