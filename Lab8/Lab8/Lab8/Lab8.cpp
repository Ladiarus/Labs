#include "Lab8.h"
#include "LadiarusSpace.h"
int n;
string curr_in_file, curr_out_file;
vector <int> outWeigths{12, 5, 5, 7, 6, 6, 6, 6};
ifstream fin;
ofstream fout;
fstream createStream;

void viewOptions()
{
    cout << "Create - 1\nChoose - 2\nAdd - 3\nChange - 4\n";
    int c;
    chooseOption(curr_in_file, {createFileSelect, chooseFileSelect});
}
bool isFileExists(string s)
{
    createStream.close();
    createStream.open(s, ios::in);
    if (createStream.is_open())
    {
        createStream.close();
        return true;
    }
    else
    {
        createStream.close();
        return false;
    }
}
void viewFile()
{
    system("cls");
    cout << "----------------------" << curr_in_file << "----------------------\n";
    string s;
    fin.close();
    fin.open(curr_in_file);
    fin.seekg(ios::beg);
    while (!fin.eof())
    {
        getline(fin, s);
        vector <string>v = splitStr(s, ' ');
        for(int i = 0; i < v.size(); i++)
            cout << setw(outWeigths[i]) << v[i];
        cout << endl;
    }
    viewOptions();
}
void clearFile(string s)
{
    if (isFileExists(s))
    {
        createStream.open(s, ios::out);
        createStream.close();
    }
    else
    {
        bool b;
        cout << "Файла не существует, создать его? y/n\n";
        input(b);
        if(b)
            createStream.open(s, ios::out);
        createStream.close();
        
    }
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
        createStream.open(s, ios::out);\
        createStream.close();
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
}
void chooseOption(string s, vector<void(*)()> args)
{
    int choice;
    input(choice, 1, args.size());
    for (int i = 0; i < args.size(); i++)
    {
        if (i + 1 == choice)
            args[i]();
    }
}
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    fin.open("input.txt");
    curr_in_file = "input.txt";
    fout.open("output.txt");
    curr_out_file = "output.txt";
    while (true)
    {
        viewFile();

    }
    system("pause");
}