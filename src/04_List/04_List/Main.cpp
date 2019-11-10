#include <iostream>
#include "List.h"
#include "Tests.h"
using namespace std;

void main()
{
    Tests1();//Поиск
    Tests2();//Вставка в конец
    Tests3();//Вставка в начало
    Tests4();//Вставка после
    Tests5();//Вставка до
    Tests6();//Удаление
    Tests7();//Конструктор копирования
    int i;
    cin >> i;
}