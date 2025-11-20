#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human 
{
    protected:
        string name;
        int age;
    public:
        Human(const string& n, int a) : name(n), age(a)
        {
            if (a >= INT_MAX-1000)
            {
                throw overflow_error("Возможно переполнение типа int ");
            }
        }

        virtual void display() const {
            cout << "Имя: " << name << ", Возраст: " << age;
        }

        virtual ~Human() = default;
};

class Preschooler : public Human 
{
    private:
        string kindergarten;
    public:
        Preschooler(const string& n, int a, const string& kg)
            : Human(n, a), kindergarten(kg) {}

        void display() const override {
            Human::display();
            cout << ", Детский сад: " << kindergarten << endl;
        }
};

class Schoolchild : public Human 
{
    private:
        int grade;
        string school;
    public:
        Schoolchild(const string& n, int a, int g, const string& s)
            : Human(n, a), grade(g), school(s) {}

        void display() const override 
        {
            Human::display();
            cout << ", Класс: " << grade << ", Школа: " << school << endl;
        }
};

class Student : public Human
{
    private:
        string university;
        string major;
    public:
        Student(const string& n, int a, const string& u, const string& m)
            : Human(n, a), university(u), major(m) {}

        void display() const override 
        {
            Human::display();
            cout << ", ВУЗ: " << university << ", Специальность: " << major << endl;
        }
};

class Worker : public Human 
{
    private:
        string company;
        string position;
    public:
        Worker(const string& n, int a, const string& c, const string& p)
            : Human(n, a), company(c), position(p) {}

        void display() const override 
        {
            Human::display();
            cout << ", Компания: " << company << ", Должность: " << position << endl;
        }
};

template<typename T>
class PointerArray 
{
    private:
        vector<T*> pointers;
    public:
        void add(T* ptr) 
        {
            pointers.push_back(ptr);
        }
        T*& operator[](size_t index) 
        {
            if (index >= pointers.size()) 
            {
                throw out_of_range("Индекс выходит за границы массива");
            }
            return pointers[index];
        }
        size_t size() const
        {
            return pointers.size();
        }
        ~PointerArray() 
        {
            for (auto ptr : pointers) {
                delete ptr;
            }
        }
};

int main() 
{
    setlocale(LC_ALL, "RU");

    cout << "Массив указателей на базовый класс Human:" << endl;
    Preschooler* child = new Preschooler("Аня", 6, "Солнышко");
    Schoolchild* pupil = new Schoolchild("Петя", 12, 6, "Школа №15");
    Student* student = new Student("Мария", 20, "МГУ", "Информатика");
    Worker* worker = new Worker("Иван", 35, "ООО ТехноПро", "Инженер");
    PointerArray<Human> humanArray;
    humanArray.add(child);
    humanArray.add(pupil);
    humanArray.add(student);
    humanArray.add(worker);
    for (size_t i = 0; i < humanArray.size(); i++) 
    {
        cout << "Элемент " << i << ": ";
        humanArray[i]->display();
    }
    cout << endl;


    cout << "Массив указателей на конкретные классы:" << endl;
    cout << "Массив студентов:" << endl;
    PointerArray<Student> studentArray;
    studentArray.add(new Student("Алексей", 22, "МГТУ", "Физика"));
    studentArray.add(new Student("Ольга", 19, "МГУ", "Математика"));
    for (size_t i = 0; i < studentArray.size(); i++) 
    {
        cout << "Студент " << i << ": ";
        studentArray[i]->display();
    }
    cout << endl;

    cout << "Массив работников:" << endl;
    PointerArray<Worker> workerArray;
    workerArray.add(new Worker("Сергей", 40, "Google", "Разработчик"));
    workerArray.add(new Worker("Елена", 28, "Яндекс", "Дизайнер"));
    for (size_t i = 0; i < workerArray.size(); i++) 
    {
        cout << "Работник " << i << ": ";
        workerArray[i]->display();
    }
    cout << endl;


    cout << "Демонстрация обработки исключений:" << endl;
    try 
    {
        humanArray[10]->display();
    }
    catch (const out_of_range& e) 
    {
        cout << "Ошибка: " << e.what() << endl;
    }
    try
    {
        Preschooler* child = new Preschooler("Аня", INT_MAX - 200, "Солнышко");
    }
    catch (const overflow_error& e)
    {
        cout << "Ошибка: " << e.what() << endl;
    }

    return 0;
}