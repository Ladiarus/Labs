#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
template <class T>
void input(T& a);


void input(int& x, int a, int b);

void input(bool& b);

void input(string &s, string exclude);

vector<string> splitStr(string s, char delim);