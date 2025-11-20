#include <iostream>
#include <string>

using namespace std;

class Publication
{
protected:
    string title;
    float price;
public:
    void getdata()
    {
        cout << "Enter the title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the price: ";
        cin >> price;
    }

    void putdata() const
    {
        cout << "Title: " << title << endl;
        cout << "Price: " << price << endl;
    }
};

class Sales
{
protected:
    float sales_data[3];
public:
    void get_sales_data()
    {
        cout << "Enter the sales for the last 3 months: ";
        for (int i = 0; i < 3; i++)
        {
            cin >> sales_data[i];
        }
    }

    void put_sales_data() const
    {
        cout << "Sales in the last 3 months: ";
        for (int i = 0; i < 3; i++)
        {
            cout << sales_data[i]<<endl;
        }
    }
};

class Book : public Publication, public Sales
{
private:
    int page_count;
public:
    void getdata()
    {
        Publication::getdata();
        cout << "Enter number of pages: ";
        cin >> page_count;
        Sales::get_sales_data();
    }

    void putdata() const
    {
        Publication::putdata();
        cout << "Number of pages: " << page_count << endl;
        Sales::put_sales_data();
    }
};

class Type : public Publication, public Sales
{
private:
    float play_time;
public:
    void getdata()
    {
        Publication::getdata();
        cout << "Enter recording time (in minutes): ";
        cin >> play_time;
        Sales::get_sales_data();
    }

    void putdata() const
    {
        Publication::putdata();
        cout << "Recording time: " << play_time << " minutes" << endl;
        Sales::put_sales_data();
    }
};

int main()
{
    Book book1;
    Type audio1;

    cout << "Enter book data" << endl;
    book1.getdata();

    cout << "Enter audiobook data" << endl;
    audio1.getdata();

    cout << "Book data:" << endl;
    book1.putdata();

    cout << "Audiobook data:" << endl;
    audio1.putdata();

    return 0;
}