#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Базовый класс - Деталь
class Detail
{
protected:
    string name;

    // Конструктор в protected - нельзя создавать напрямую
    Detail(const string& n) : name(n) {}

public:
    // Виртуальный метод для вывода информации
    virtual void print() const
    {
        cout << "Деталь: " << name << endl;
    }

    // Виртуальный деструктор для правильного удаления
    virtual ~Detail() {}

    // Дружественная шаблонная функция для создания объектов
    // Args... - пакет аргументов
    template<typename T, typename... Args>
    friend T* create(Args... args);
};

// Производный класс - Сборка
class Assembly : public Detail
{
protected:
    // Конструктор в protected
    Assembly(const string& n) : Detail(n) {}

public:
    // Переопределяем метод print
    void print() const override
    {
        cout << "Сборка: " << name << endl;
    }

    // Дружественная шаблонная функция
    template<typename T, typename... Args>
    friend T* create(Args... args);
};

// Шаблонная дружественная функция для создания объектов
template<typename T, typename... Args>
T* create(Args... args)
{
    // Создаем объект и возвращаем указатель на него
    return new T(args...);
}

int main()
{
    setlocale(LC_ALL, "ru");
    // Вектор для хранения указателей на объекты
    vector<Detail*> storage;

    // Создаем объекты с помощью дружественной функции
    // и добавляем их в хранилище
    storage.push_back(create<Detail>("Болт"));
    storage.push_back(create<Detail>("Гайка"));
    storage.push_back(create<Assembly>("Двигатель"));
    storage.push_back(create<Assembly>("Корпус"));

    // Выводим информацию о всех объектах
    cout << "Содержимое хранилища:" << endl;
    for (Detail* item : storage) {
        item->print();  // Полиморфный вызов
    }

    // Очищаем память
    for (Detail* item : storage) {
        delete item;
    }

    return 0;
}