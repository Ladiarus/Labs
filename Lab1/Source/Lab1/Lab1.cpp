#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double x(2.444), y(0.869e-2), z(-0.13e3), h;
    cout << "йфыв";
    h = (pow(x, y + 1) + exp(y - 1)) / (1 + x * abs(y - tan(z))) * (1 + abs(y - x)) 
        + pow(abs(y - x), 2) / 2 - pow(abs(y - x), 3) / 3;
    cout << h << "\n";
    system("Pause");
}