#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "Введите натуральное число: ";
    int x;
    cin >> x;
    if (x <= 0)
    {
        cout << "Введенное число не натурально! Прервано." << endl;
        return 0;
    }
    srand(time(NULL));
    cout << "Случайное число в диапозоне [1, " << x << "]: " << (rand() % x) + 1 << endl;
    return 0;
}
