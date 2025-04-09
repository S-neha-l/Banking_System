#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct record
{
    int day, mon, yr;
    int accno;
    char name[30];
    int balance;
};

void display(record *t, int no);
int main()
{
    ifstream r;
    r.open("Files\\rec.bin", ios::binary);

    if(r.is_open() == false)
    {
        cerr<<"Error: Cannot create file.\n";
        return 1;
    }

    int no, i;
    r.read((char *)&no, sizeof(int));
    record rec[no], *ptr;

    for(i=0; i<no; i++) 
    {
        ptr = (rec + i);
        r.read((char *)ptr, sizeof(record));
    }

    display(rec, no);
    r.close();
    return 0;
}

void display(record *t, int no)
{
    int i;
    record *rec;
    cout<<"Record file: \n";
    cout<<setw(10)<<"Date"<<setw(12)<<"Acc. no"<<setw(11)<<"Name"<<setw(15)<<"Balance"<<"\n";

    for(i=0; i<no; i++)
    {
        rec = (t + i);
        cout<<setw(5)<<rec->day<<"-"<<rec->mon<<"-"<<rec->yr;
        cout<<setw(9)<<rec->accno;
        cout<<setw(12)<<rec->name;
        cout<<setw(14)<<rec->balance;
        cout<<"\n";
    }
}