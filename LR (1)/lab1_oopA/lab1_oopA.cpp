#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    int length;
    cout << "Введите длину массива: ";
    cin >> length;
    if (length <= 0)
    {
        cout << "Некорректное число" << endl;
        exit(0);
    }
    int* mas = new int[length];
    cout << "Заполните массив: "<<endl;
    for (int i = 0; i < length; i++)
    {                                     
        cin >> mas[i];
    }
    for (int i = 0; i < length; i++)
    {
        cout << "mas[" << i << "] = " << mas[i] << endl;
    }
    cout << "Адрес начала массива: " << mas << endl;
    cout << "Расстояние элементов от начала массива:" << endl;
    for (int i = 1; i < length; i++)
    {
        int distance = &mas[i] - mas;
        cout << "Элемент mas[" << i << "]. Адрес: "<< &mas[i] <<". Расстояние " << distance*sizeof(int) << " байта" << endl;
    }
    delete[] mas;
    return 0;
}