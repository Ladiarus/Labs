#pragma once
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_DELETE 83
#define KEY_BACKSPACE 8
#define NAME_INPUT_CHECK (c >= 'a' && c <= 'z' || c-255 >= 'à' && c-255 <= 'ÿ' || c >= 'A' && c <= 'Z' || c-255 >= 'À' && c-255 <= 'ß' || c == ' ')
#define DOUBLE_INPUT_CHECK (c >= '0' && c <= '9' || c == '.')
#define INT_INPUT_CHECK (c >= '0' && c <= '9')
#define TO_ROW(num) (cout<<"\033["+to_string(num)+"G")
#define CLEAR_LINE() (cout<<"\033[2K")
#define UP_LINE() (cout << "\033[1A")

enum dataType
{
	String,
	Double,
	Int
};

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <list>
#include <vector>
#include <Windows.h>
using namespace std;

struct StudentData
{
	double marks[4]{}, average_mark = 0;
	string name;
	int year = 0, number = 0;
};

void moveChar(int x, int y);

void viewOptions();

bool isFileExists(string s);

void viewFile();

void clearFileSelect();

void clearFile(string s);

void createFileSelect();

void createFile(string s);

void chooseFileSelect();

void chooseFile(string s);

void chooseOption(vector<void(*)()> args);

void editRowSelect();

void editRow(int idx, StudentData sd);

void sortSelect();

void sort(vector<StudentData> v, bool reverse, bool(*comp)(StudentData*, StudentData*));

void addStringSelect();

void addString(string path, const StudentData* sd);

StudentData editStudentDataViaGetch(StudentData sd);

string editString(string curr_s, dataType data_type, double min_val = 0, double max_val = 0);

StudentData getStudentDataByIdx(int idx);

StudentData getStudentDataByString(string &s);

bool isNameValid(string s);

bool isDoubleValid(string s);

bool isIntValid(string s , int a, int b);

void individualTaskSelect();
