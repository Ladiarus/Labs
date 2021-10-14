#pragma once
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
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

void editStringSelect();
struct StudentData
{
	double marks[4]{}, average_mark = 0;
	string name;
	int year = 0, number = 0;
};

void addStringSelect();

void addString(string path, const StudentData* sd);