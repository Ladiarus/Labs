#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Lab8.h"
template <class T>
void input(T& a);


void input(int& x, int a, int b);

void input(double& x, double a, double b);

void input(bool& b);

void input(string &s, string exclude);

vector<string> splitStr(string s, char delim);
int clamp(int n, int lower, int upper);

string centerString(const string& s, int width, char fill_with);

