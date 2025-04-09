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

void display(transaction *t, int no);
int main()
{
    ifstream in;
    in.open("Files\\txn.bin", ios::binary);

    if(in.is_open() == false)
    {
        cerr<<"Cannot locate file (file: txn.bin).\n";
        return 1;
    }

    //Read:
    int i, no;
    in.read((char *)&no, sizeof(int));
    transaction t[no];
    for(i=0; i<no; i++) in.read((char *)&t[i], sizeof(transaction));

    display(t, no);

    in.close();
    return 0;
}

void display(transaction *t, int no)
{
    transaction *txnptr;
    int i;
    cout<<"Deposit file: \n";
    cout<<setw(10)<<"Date"<<setw(12)<<"Acc. no"<<setw(13)<<"Name"<<setw(15)<<"Deposit"<<setw(15)<<"Withdraw"<<setw(15)<<"Balance"<<"\n";
    for(i=0; i<no; i++)
    {
        txnptr = (t + i);
        cout<<setw(5)<<txnptr->day<<"-"<<txnptr->month<<"-"<<txnptr->yr;
        cout<<setw(8)<<txnptr->accno;
        cout<<setw(15)<<txnptr->name;
        cout<<setw(12)<<txnptr->deposit;
        cout<<setw(15)<<txnptr->withdraw;
        cout<<setw(16)<<txnptr->balance<<"\n";      
    }
}