#include <iostream>
#include "TMatrix.h"
#include "Tests.h"
using namespace std;

void main()
{
    Tests1();//A + B
    Tests2();//A - B
    Tests3();//A * B
    Tests4();//A + const
    Tests5();//A - const
    Tests6();//A * const
    Tests7();//A * vec
    Tests8();//A == B
    Tests9();//A != B
}