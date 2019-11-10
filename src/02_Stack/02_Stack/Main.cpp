#include "PF.h"
#include <iostream>

using namespace std;

void main()
{
    string s;
    cin >> s;
    PolF PF(s);
    PF.PrintPF();
    PF.ZN();
    cout << PF.Count(); cin >> s;
}