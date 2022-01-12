#include "Lab8.h"
#include "LadiarusSpace.h"
int amount_of_lines;
short current_pointer_y;
bool is_exit;
const string INDIVIDUAL_TASK_FILE_NAME = "Individual Task.txt";
const string TEMP_FILE_NAME = "TEMP_FILE_DO_NOT_TOUCH.txt";
COORD curr_coord;
CONSOLE_SCREEN_BUFFER_INFO info;
string curr_in_file, curr_out_file;
const int OUT_WEIGTHS[] = {19, 5, 8, 5, 5, 5, 5, 7};
ifstream fin;
ofstream fout;
fstream finout;
HANDLE hCon;

template <typename T>
void myQSort(vector<T>& v, int beg, int end, bool(*comp)(T*, T*))
{
    int curr_main_idx = end;
    if (end <= beg)
    {
        
        return;
    }
    int i = beg;
    while (i < curr_main_idx)
    {
        if (comp(&v[i], &v[curr_main_idx]))
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

bool intComp(int* a, int* b)
{
    return *a > *b;
}

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

StudentData getStudentDataByIdx(int idx)
{
    string s;
    fin.close();
    fin.open(curr_in_file);
    for(int i = 0; i < idx-1; i++)
    {
        fin.ignore(INT_MAX, '\n');
    }
    getline(fin, s);
    return getStudentDataByString(s);

}

StudentData getStudentDataByString(string &s)
{
    StudentData sd;
    vector <string> v = splitStr(s, ' ');
    sd.name = v[0] + " " + v[1];
    sd.year = stoi(v[2]);
    sd.number = stoi(v[3]);
    for (int i = 4; i < 8; i++)
    {
        sd.marks[i - 4] = stod(v[i]);
    }
    sd.average_mark = stod(v[8]);
    return sd;
}

bool isNameValid(string s)
{
    vector <string> v = splitStr(s, ' ');
    if (v.size() != 2)
    {
        cout << "\nНеверный ввод, введите через пробел фамилию и инициалы\n";
        return false;
    }
    for (char c : s)
    {
        if (!(isalpha(c) || (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я')) && c != ' ' && c != '.')
        {
            return false;
        }
    }
    if (s.length() > 19)
    {
        cout << "\nМаксимальная длина " << OUT_WEIGTHS[0] << " символов\n";
        return false;

    }
    return true;
}

bool isDoubleValid(string &s, double a, double b)
{
    int num_of_dots = 0;
    if (s[0] == '.')
        s = '0' + s;
    if (s.length() > 15)
        return false;
    for (auto c : s)
        if (c == '.')
            num_of_dots++;

    if (num_of_dots > 1)
        return false;
    double x = stod(s);
    if (x < a || x > b)
        return false;
    return true;
}

bool isIntValid(string s, int a, int b)
{
    if (s.length() > 10)
        return false;
    long long x = stol(s);
    if (x < a || x > b)
        return false;
    return true;
}

void viewOptions()
{
    cout << "Create File - 1\nChoose File - 2\nAdd - 3\nChange - 4\nDelete - 5\nSort - 6\nIndividual Task - 7\n";
    chooseOption({createFileSelect, chooseFileSelect, addStringSelect, editRowSelect, deleteSelect, sortSelect, individualTaskSelect});
}

bool isFileExists(string s)
{
    finout.close();
    finout.open(s, ios::in);
    if (finout.is_open())
    {
        finout.close();
        return true;
    }
    else
    {
        finout.close();
        return false;
    }
}

void viewFile()
{
    system("cls");
    cout << " " << centerString(curr_in_file, 67, '-') << "\n"
        " |        Имя        | Год | Группа | Физ | Мат | Инф | Хим | Средн |\n"
		" |-------------------|-----|--------|-----|-----|-----|-----|-------|\n";
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
                cout << "\033[48;5;235m"; // background color
            }
            cout << "|" << setw(OUT_WEIGTHS[0]) << v[0] + " " + v[1] << "|";

            for (int i = 2; i < v.size(); i++)
            {
                cout << setw(OUT_WEIGTHS[i - 1]) << v[i] << '|';
            }
            cout << ' ' << "\033[34m" << amount_of_lines + 1 << "\033[m" << endl ;
            
        }
        if(!s.empty())  
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
    bool b;
    string s;
    cout << "Введите название файла, оканчивающееся на .txt\n";
    do {
        input(s, "/<>?|*:\"\\");
        if (s.length() <= 4 || s.substr(s.length() - 4, 4) != ".txt")
            cout << "Неверный ввод\n\a";
    } while (s.length() <= 4 || s.substr(s.length() - 4, 4) != ".txt");
    if (isFileExists(s))
    {
        cout << "Файл существует, очистить его? y/n\n";
        input(b);

        if (b)
            clearFile(s);
    }
    else
    {
		createFile(s);
    }
    cout << "Файл создан, открыть его? y/n\n";
    input(b);
    if(b)
    {
        chooseFile(s);
    }
}
void createFile(string s)
{
    finout.close();
	finout.open(s, ios::out);
    finout.close();

}

void chooseFileSelect()
{
    string s;
    cout << "Введите название файла, оканчивающееся на .txt\n";
    do {
        input(s, "/<>?|*:\"\\");
        if (s.length() <= 4 || s.substr(s.length() - 4, 4) != ".txt")
            cout << "Неверный ввод\a\n";
    } while (s.length() <= 4 || s.substr(s.length() - 4, 4) != ".txt");
    if (!isFileExists(s))
    {
        bool b;
        cout << "Файла не существует, создать его? y/n\n";
        input(b);
        if (b)
        {
            createFile(s);
        }
    }
    else
    {
		chooseFile(s);
	    
    }
}
void chooseFile(string s)
{
    if (s != INDIVIDUAL_TASK_FILE_NAME)
    {
        fin.close();
        fin.open(s);
        curr_in_file = s;
    }
    else
    {
        cout << "Этот файл нельзя открывать";
    }
}

void editRowSelect()
{
    if (amount_of_lines == 0)
        return;
    int c = 0, y, selected_idx = -1;
    bool isInPointerMode = false;
    cout << "Выберите строку, которую хотите изменить (Стрелка Вверх(Вниз), чтобы переместить указатель)\n";
    cout << "Нажмите ESC, чтобы выйти из режима указателя и ввести номер строки\n";
    GetConsoleScreenBufferInfo(hCon, &info);
    curr_coord = info.dwCursorPosition;


    while (true)
    {
        int c = _getch();
        if (c == 224) { 

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
        else if(c == KEY_ENTER) //если нажат Enter
        {
            selected_idx = current_pointer_y - 2;
            resetCursor();
            break;
        }
        else if (c == 27)//если нажат ESC
        {
            resetCursor();
            break;
        }
    }
    if (selected_idx == -1)
    {
        input(selected_idx, 1, amount_of_lines);
    }

    StudentData sd = editStudentDataViaGetch(getStudentDataByIdx(selected_idx));
    editRow(selected_idx, sd);
}
void editRow(int idx, StudentData sd)
{
    string s;
    fin.close();
    fin.open(curr_in_file);
    createFile(TEMP_FILE_NAME);
    fout.open(TEMP_FILE_NAME);

    for(int i = 0; i < idx-1; i++)
    {
        getline(fin, s);
        fout << s << endl;
    }
    sd.average_mark = (sd.marks[0] + sd.marks[1]+sd.marks[2] + sd.marks[3])/4;
    fin.ignore(INT_MAX, '\n');
    fout << sd.name << ' ';
    fout << sd.year << ' ';
    fout << sd.number << ' ';
    fout << round(sd.marks[0] * 10) / 10 << ' ';
    fout << round(sd.marks[1] * 10) / 10 << ' ';
    fout << round(sd.marks[2] * 10) / 10 << ' ';
    fout << round(sd.marks[3] * 10) / 10 << ' ';
    fout << round(sd.average_mark * 10) / 10;

    while(!fin.eof())
    {
        getline(fin, s);
        fout << "\n" << s;
    }
    fin.close();
    fout.close();
    remove(curr_in_file.c_str());
    rename(TEMP_FILE_NAME.c_str(), curr_in_file.c_str());
}

void sortSelect()
{
    int c, a;
    if (amount_of_lines == 0)
        return;
    vector<StudentData> v;
    fin.close();
    fin.open(curr_in_file);
    string s;
    while(!fin.eof())
    {
        getline(fin, s);
        v.push_back(getStudentDataByString(s));
    }

    cout << "Имя - 1\nГод - 2\nНомер - 3\nФизика- 4\nМатематика - 5\nИнформатика - 6\nХимия - 7\nСредняя - 8\nEXIT - 0\n";
    input(c, 0, 8);
    if (c == 0)
        return;
    cout << "От большего к меньшему - 1\nОт меньшего к большему - 2\n";
    input(a, 1, 2);
    bool reverse = a - 1;

    switch(c)
    {
    case 1:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->name < sd2->name;
        });
        break;
    case 2:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->year < sd2->year;
        });
        break;
    case 3:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->number < sd2->number;
        });
        break;
    case 4:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->marks[0] < sd2->marks[0];
        });
        break;
    case 5:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->marks[1] < sd2->marks[1];
        });
        break;
    case 6:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->marks[2] < sd2->marks[2];
        });
        break;
    case 7:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->marks[3] < sd2->marks[3];
        });
        break;
    case 8:
        sort(v, reverse, [](StudentData* sd1, StudentData* sd2) ->bool
        {
	        return sd1->average_mark < sd2->average_mark;
        });
        break;
    default:;
    }

}

void sort(vector<StudentData> v, bool reverse, bool(*comp)(StudentData*, StudentData*))
{
    myQSort<StudentData>(v, 0, v.size() - 1, comp);
    if(reverse)
    {
        std::reverse(v.begin(), v.end());
    }
    fin.close();
    fout.open(curr_in_file);
    for(int i = 0; i < v.size(); i++)
    {
        StudentData sd = v[i];
        fout << sd.name << ' ';
        fout << sd.year << ' ';
        fout << sd.number << ' ';
        fout << round(sd.marks[0] * 10) / 10 << ' ';
        fout << round(sd.marks[1] * 10) / 10 << ' ';
        fout << round(sd.marks[2] * 10) / 10 << ' ';
        fout << round(sd.marks[3] * 10) / 10 << ' ';
        fout << round(sd.average_mark * 10) / 10;
        if (i < v.size() - 1)
            fout << endl;
    }
    fout.close();

}

void cmdDeleteLeft(int &idx, string &s)
{
    if (idx <= 0)
        return;
    idx = clamp(idx, 1, s.length());
    idx --;
    char c;
    s = s.substr(0, idx) + s.substr(idx + 1, s.length() - idx);
    TO_ROW(s.length() + 1);
	cout<< " "; //в n столбец

    TO_ROW(0);
    cout << s;
    TO_ROW(idx+1);
}
void cmdDeleteRight(int& idx, string& s)
{
    if (idx >= s.length())
        return;
    idx = clamp(idx, 0, s.length()-1);
    char c;
    s = s.substr(0, idx) + s.substr(idx + 1, s.length() - idx);
    TO_ROW(s.length()+1);
    cout << " "; 

    TO_ROW(0);
    cout << s;
   TO_ROW(idx + 1);
}
void cmdAdd(int& idx, string& s, int c)
{
    
    string temp_s = s.substr(0, idx);
    s = temp_s + static_cast<char>(c) + s.substr(idx, s.length() - idx);
    TO_ROW(0);
    cout << s;
    TO_ROW(idx + 2);
    idx++;
}

StudentData editStudentDataViaGetch(StudentData sd)
{
    cout << "Имя\n";
    cout << sd.name;
    sd.name = editString(sd.name, dataType::String);
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    cout << "Год\n";
    cout << sd.year;
    sd.year = stoi(editString(to_string(sd.year), dataType::Int, 1900, 2021));
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    cout << "Номер\n";
    cout << sd.number;
    sd.number = stoi(editString(to_string(sd.number), dataType::Int, 0, 99999999));
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    for (int i = 0; i < 4; i++)
    {
        switch(i)
        {
        case 0:
            cout << "Физика\n";
            break;
        case 1:
            cout << "Математика\n";
            break;
        case 2:
            cout << "Информатика\n";
            break;
        case 3:
            cout << "Химия\n";
            break;
        }
        cout << to_string(sd.marks[i]);
        sd.marks[i] = stod(editString(to_string(sd.marks[i]), dataType::Double, 0, 10));
        CLEAR_LINE();
        UP_LINE();
        CLEAR_LINE();
        TO_ROW(0);
    }
    
    return sd;
}
string editString(string curr_s, dataType data_type, double min_val, double max_val)
{
    int curr_pos = 0;
    TO_ROW(0);
    while (true)
    {
        bool isA;
        int c = _getch();
        if (c == 224) {

            if(_kbhit()) // если ожидает ввода (не 'а')
            {
                switch (_getch())
                {
                case KEY_LEFT:
                    if (curr_pos > 0)
                    {
                        cout << "\033[1D"; //влево
                        curr_pos--;
                    }
                    break;
                case KEY_RIGHT:
                    if (curr_pos < curr_s.length())
                    {
                        cout << "\033[1C"; //вправо
                        curr_pos++;
                    }
                    break;
                case KEY_DELETE:
                    cmdDeleteRight(curr_pos, curr_s);
                    break;
                }
                continue;
            }
        }
        else if (c == KEY_ENTER)
        {
            if (!curr_s.empty())
            {
                switch (data_type)
                {
                case String:
                    if (isNameValid(curr_s))
                        return curr_s;
                    break;
                case Double:
                    if (isDoubleValid(curr_s, min_val, max_val))
                        return curr_s;
                    break;
                case Int:
                    if (isIntValid(curr_s, min_val, max_val))
                    {
                        return curr_s;
                    }
                    break;
                }
                TO_ROW(0);
                cout << curr_s;
                TO_ROW(curr_pos + 1);
            }
        	cout << "\a"; // звук
            continue;
        }
        else if (c == KEY_BACKSPACE)
        {
            cmdDeleteLeft(curr_pos, curr_s);
            continue;
        }

        bool is_ok = false;
        int k;
        if('р' < 0 ) k = c - 256; // char почему-то signed ¯\_(ツ)_/¯
        switch (data_type)
        {
        case String:
            if (NAME_INPUT_CHECK)
            {
                is_ok = true;
            }
            break;
        case Double:
            if (DOUBLE_INPUT_CHECK)
            {
                is_ok = true;
            }
            break;
        case Int:
            if (INT_INPUT_CHECK)
            {
                is_ok = true;
            }
            break;
		}
        if(is_ok)
			cmdAdd(curr_pos, curr_s, c);
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
    StudentData *sd = new StudentData();
    bool is_valid = false;
    cout << "Введите фамилию и через пробел инициалы\n";
    cin.ignore(1000, '\n');
    while (!is_valid)
    {
	    int sum = 0;
        getline(cin, s);
        is_valid = isNameValid(s);
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
    if(amount_of_lines!=0)
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

void individualTaskSelect()
{
    if (amount_of_lines == 0)
        return;
    string s;
    double average;
    createFile(INDIVIDUAL_TASK_FILE_NAME);
    fout.open(INDIVIDUAL_TASK_FILE_NAME);
    cout << "Введите средний балл\n";

    input(average, 0, 10);

    system("cls");
    cout << centerString(INDIVIDUAL_TASK_FILE_NAME, 67, '-') << "\n"
        "|        Имя        | Год | Группа | Физ | Мат | Инф | Хим | Средн |\n"
        "|-------------------|-----|--------|-----|-----|-----|-----|-------|\n";
    fin.close();
    fin.open(curr_in_file);
    int i = 0;
    while (!fin.eof())
    {
        if(i % 2 == 0)
            cout << "\033[48;5;235m"; // background color
        getline(fin, s);
        StudentData sd = getStudentDataByString(s);
        if(sd.average_mark > average)
        {
            
            cout << "|" << setw(OUT_WEIGTHS[0]) << sd.name;
            cout << "|" << setw(OUT_WEIGTHS[1]) << sd.year;
            cout << "|" << setw(OUT_WEIGTHS[2]) << sd.number;
            cout << "|" << setw(OUT_WEIGTHS[3]) << sd.marks[0];
            cout << "|" << setw(OUT_WEIGTHS[4]) << sd.marks[1];
            cout << "|" << setw(OUT_WEIGTHS[5]) << sd.marks[2];
            cout << "|" << setw(OUT_WEIGTHS[6]) << sd.marks[3];
            cout << "|" << setw(OUT_WEIGTHS[7]) << sd.average_mark << "|";
            cout << "\033[m" << endl;
            
            fout << sd.name;
            fout << " " << sd.year;
            fout << " " << sd.number;
            fout << " " << sd.marks[0];
            fout << " " << sd.marks[1];
            fout << " " << sd.marks[2];
            fout << " " << sd.marks[3];
            fout << " " << sd.average_mark << " ";
            fout << endl;
			i++;
        }
        
    }
    cout << "\033[m" << endl;
    system("pause");
    fout.close();

}

void deleteSelect()
{
    fin.close();
    cout << "Введите через пробел номера студентов, которых хотите удалить\n";
    string s;
    int a = 0;
    bool isValid;
    cin.ignore();
    getline(cin, s);
    vector<int> linesRaw;
    vector<string> v = splitStr(s, ' ');

    for(string x : v)
    {
        isValid = true;
	    for(int i = 0; i < x.length(); i++)
	    {
		    if(x[i] < '0' || x[i] > '9')
		    {
                cout << "Неверный ввод: " + x + " будет пропущено" << endl;
                isValid = false;
                break;
		    }
	    }
        if(isValid)
        {
            a = stoi(x);
            if(a > amount_of_lines || a < 1)
            {
                cout << "Неверный ввод, выход за пределы: " + x + " будет пропущено" << endl;
            }
            else
            {
                linesRaw.push_back(a);
            }
        }
    }
    if (linesRaw.empty())
        return;
    myQSort<int>(linesRaw, 0, linesRaw.size() - 1, intComp);
    vector<int> lines;
    lines.push_back(linesRaw[0]);
    for(int i = 1; i < linesRaw.size(); i++)
    {
	    if(linesRaw[i] != linesRaw[i - 1])
	    {
            lines.push_back(linesRaw[i]);
	    }
    }
    int arrIdx = 0, fileIdx = 1;
    fin.open(curr_in_file);
    string g, k;
    cout << "Будут удалены:\n";
    while(!fin.eof() && arrIdx < lines.size())
    {
        if (fileIdx == lines[arrIdx])
        {
            fin >> g;
            fin >> k;
            cout << g + " " + k << endl;
            arrIdx++;
        }
        fin.ignore(INT_MAX, '\n');
        fileIdx++;
    }

    bool b;
    cout << "Вы уверены, что хотите удалить эти записи? y/n\n";
    input(b);
    if(b)
		deleteRows(lines);


}

void deleteRows(vector<int>& v)
{
    string s;
    v.push_back(-1); //Ограничитель
    fin.close();
    fin.open(curr_in_file);
    createFile(TEMP_FILE_NAME);
    fout.open(TEMP_FILE_NAME);
    int fileIdx = 1;
    int arrIdx = 0;
    bool is_first_write = true;
    while (!fin.eof())
    {
        if(fileIdx != v[arrIdx])
        {
            getline(fin, s);
            if(!is_first_write) //если не первая строка
            {
                fout << "\n";
            }
        	fout << s;
            is_first_write = false;
        }
        else
        {
            fin.ignore(INT_MAX, '\n');
            arrIdx++;
        }
    	fileIdx++;
    }
    fin.close();
    fout.close();
    remove(curr_in_file.c_str());
    rename(TEMP_FILE_NAME.c_str(), curr_in_file.c_str());
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "en-US"); // устанавливаю locale для цифр и знаков, чтобы работал stod
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Присваивание дескриптора консоли

    COORD  size{ 100, 50 };
    SetConsoleScreenBufferSize(hCon, size);//размер буфера
    
    fin.open("input.txt");
    curr_in_file = "input.txt";
    while (true)
    {
    	viewFile();
        if(is_exit)
            break;
    }
}