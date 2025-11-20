#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class BookType
{
    художественная,    
    техническая  
};

class Book
{
    public:
        string author;
        string title;
        BookType type;
        Book(const string& auth, const string& titl, BookType t)
        {
            author = auth;
            if (author.empty())
            {
                throw invalid_argument("Автор не может быть пустым");
            }
            title = titl;
            if (title.empty())
            {
                throw invalid_argument("Название не может быть пустым");
            }
            type = t;
        }
        ~Book() {}
};

class Library
{
    private:
        vector<Book*> books;
    public:
        void addBook(Book* book)
        {
            books.push_back(book);
        }

        void countSwitch()
        {
            int XCount = 0;
            int TCount = 0;

            for (const auto& book : books)
            {
                switch (book->type)
                {
                    case BookType::художественная:
                        XCount++;
                        break;
                    case BookType::техническая:
                        TCount++;
                        break;
                }
            }
            cout << "Подсчет с switch" << endl;
            cout << "Художественная литература: " << XCount << " книг" << endl;
            cout << "Техническая литература: " << TCount << " книг" << endl;
            cout << endl;
        }
        void count()
        {
            int XCount = 0;
            int TCount = 0;

            for (const auto& book : books) 
            {
                if (book->type == BookType::художественная) 
                {
                    XCount++;
                }
                else if (book->type == BookType::техническая) 
                {
                    TCount++;
                }
            }
            cout << "Подсчет без switch" << endl;
            cout << "Художественная литература: " << XCount << " книг" << endl;
            cout << "Техническая литература: " << TCount << " книг" << endl;
            cout << endl;
        }
        void print()
        {
            for (int i = 0; i < books.size(); i++)
            {
                string typeStr;
                if (books[i]->type == BookType::художественная) 
                {
                    typeStr = "Художественная";
                }
                else 
                {
                    typeStr = "Техническая";
                }
                cout << books[i]->author << " || " << books[i]->title << " || "<< typeStr << endl;
            }
        }
        ~Library()
        {
            for (auto& book : books) 
            {
                delete book;
            }
            books.clear();
        }
};

int main()
{
    setlocale(LC_ALL, "RU");
    Library library;
    try 
    {
        cout << "Загружаем книги в библиотеку..." << endl;

        Book* book1 = new Book("Толкин", "Властелин Колец", BookType::художественная);
        Book* book2 = new Book("Федор Достоевский", "Игрок", BookType::художественная);
        Book* book3 = new Book("Бьярне Страуструп", "Язык программирования C++", BookType::техническая);
        Book* book4 = new Book("Терри Пратчетт", "Мелкие Боги", BookType::художественная);
        Book* book5 = new Book("Дональд Кнут", "Искусство программирования", BookType::техническая);
        Book* book6 = new Book("Станислав Лем", "Непобедимый", BookType::художественная);

        library.addBook(book1);
        library.addBook(book2);
        library.addBook(book3);
        library.addBook(book4);
        library.addBook(book5);
        library.addBook(book6);

        library.print();

        library.countSwitch();

        library.count();
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}