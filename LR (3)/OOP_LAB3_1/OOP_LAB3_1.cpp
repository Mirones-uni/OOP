#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Base
{
protected:
    
    Base(int i) : id(i){}

public:
    int id;
    // Виртуальный метод клонирования - создает копию объекта
    virtual Base* clone(int n) const
    {
        return new Base(n);  // Создает копию Base
    }

    virtual void show() const
    {
        cout << "Это объект Base. id = " << id << endl;
    }

    virtual ~Base() {}

    friend Base* createBase(int n);
};

class Derived : public Base
{
protected:
    Derived(int i):Base(i) {}

public:
    Base* clone(int n) const override
    {
        return new Derived(n);  // Создает копию Derived
    }

    void show() const override
    {
        cout << "Это объект Derived. id = "<< id<< endl;
    }

    friend Base* createDerived(int n);
};

Base* createBase(int n)
{
    return new Base(n);
}

Base* createDerived(int n)
{
    return new Derived(n);
}

// Функция принимает объект и добавляет его копию в хранилище
void add(vector<Base*>& storage, Base* original) {
    Base* copy = original->clone(original->id);  // Создаем копию!
    storage.push_back(copy);
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));
    vector<Base*> storage;

    cout << "Создание объектов:" << endl;

    for (int i = 0; i < 5; i++) //распределяем создание объектов
    {
        Base* original = nullptr;

        if (rand() % 2 == 0)
        {
            cout << "Создан оригинал Base. id = " << i << endl;
            original = createBase(i);
        }
        else 
        {
            cout << "Создан оригинал Derived. id = " << i << endl;
            original = createDerived(i);
        }

        // В хранилище попадает КОПИЯ оригинала
        add(storage, original);

        // Оригинал можно удалить - в хранилище его копия
        delete original;
    }

    cout << "Показываем объекты из хранилища (копии):" << endl;
    for (int i = 0; i < storage.size(); i++)
    {
        cout << "Копия " << i + 1 << ": ";
        storage[i]->show();
    }

    // Очищаем копии в хранилище
    for (Base* obj : storage) 
    {
        delete obj;
    }

    return 0;
}