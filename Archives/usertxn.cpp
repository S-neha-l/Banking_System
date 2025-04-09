#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct transaction
{
    int day, month, yr;
    int accno;
    char name[30];
    int deposit, withdraw, balance;
};

int main()
{
    ifstream in;
    in.open("Files\\txn.bin", ios::binary);

    if(in.is_open() != true)
    {
        cerr<<"No such file found (file: txn.bin).\n";
        return 1;
    }

    int no, i, accno, count;
    in.read((char *)&no, sizeof(int));
    transaction txn[no], *t;

    cout<<"Enter account number: ";
    cin>>accno;

    //Read
    for(i=0, count=0; i<no; i++)
    {
        t = (txn + i);
        in.read((char *)t, sizeof(transaction));

        if(t->accno == accno) count++;
    }

    if(count == 0)
    {
        cout<<"No such account number is found.\n";
        return 0;
    }

    //Display
    cout<<setw(10)<<"Date"<<setw(12)<<"Acc. no"<<setw(13)<<"Name"<<setw(15)<<"Deposit"<<setw(15)<<"Withdraw"<<setw(15)<<"Balance"<<"\n";
    for(i=0; i<no; i++)
    {
        t = (txn + i);

        if(t->accno != accno) continue;
        cout<<setw(5)<<t->day<<"-"<<t->month<<"-"<<t->yr;
        cout<<setw(8)<<t->accno;
        cout<<setw(15)<<t->name;
        cout<<setw(12)<<t->deposit;
        cout<<setw(15)<<t->withdraw;
        cout<<setw(16)<<t->balance<<"\n";
    }

    in.close();
    return 0;
}