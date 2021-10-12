#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <list>
#include <vector>
#include <windows.h>
using namespace std;

void viewOptions();

bool isFileExists(string s);

void viewFile();

void clearFile(string s);

void createFileSelect();

void createFile(string s);

void chooseFileSelect();

void chooseFile(string s);

void chooseOption(string s, vector<void(*)()> args);
