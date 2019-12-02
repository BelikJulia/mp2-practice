#include <iostream>
#include "Tests.h"
using namespace std;

void Tests1()//Поиск
{
    cout << "TEST 1 search" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list;
    cout << "Search key ";
    cin >> key;
    if (list.Search(key) != 0)
    {
        cout << *(list.Search(key)) << endl << "Test 1 passed" << endl << endl;
    }
    else
    {
        cout << "No elem" << endl << "Test 1 passed" << endl << endl;
    }
}
void Tests2()//Вставка в конец
{
    cout << "TEST 2 back" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list;
    cout << "Back key ";
    cin >> key;
    cout << "Back data ";
    cin >> data;
    list.Back(key, &data);
    cout << list << endl << "Test 2 passed" << endl << endl;
}
void Tests3()//Вставка в начало
{
    cout << "TEST 3 push" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list;
    cout << " Push key ";
    cin >> key;
    cout << " Push data ";
    cin >> data;
    list.Push(key, &data);
    cout << list << endl << "Test 3 passed" << endl << endl;
}
void Tests4()//Вставка после
{
    cout << "TEST 4 InsertAfter" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key, keyS;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list;
    cout << " Push Search key ";
    cin >> keyS;
    cout << " Push key ";
    cin >> key;
    cout << " Push data ";
    cin >> data;
    try
    {
        list.InsertAfter(&data, key, keyS);
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << list << endl << "Test 4 passed" << endl << endl;
}
void Tests5()//Вставка до
{
    cout << "TEST 5 InsertBefore" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key, keyS;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list;
    cout << " Push Search key ";
    cin >> keyS;
    cout << " Push key ";
    cin >> key;
    cout << " Push data ";
    cin >> data;
    try
    {
        list.InsertBefore(&data, key, keyS);
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << list << endl << "Test 5 passed" << endl << endl;
}
void Tests6()//Удаление
{
    cout << "TEST 6 remove" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list;
    cout << " Push key ";
    cin >> key;
    try
    {
        list.Remove(key);
    }
    catch (const char* er)
    {
        cout << er << endl;
    }
    cout << list << endl << "Test 6 passed" << endl << endl;
}
void Tests7()//Конструктор копирования
{
    cout << "TEST 7 copy" << endl;
    int size;
    cout << "size = ";
    cin >> size;
    double key;
    char data;
    TList<double, char> list;
    for (int i = 0; i < size; i++)
    {
        cout << "Key = ";
        cin >> key;
        cout << "Data = ";
        cin >> data;
        list.Back(key, &data);
    }
    cout << list << endl;

    TList<double, char> list2(list);
    cout << list2;
}