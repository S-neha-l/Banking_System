//Master file (master.cpp)
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <algorithm>
#include "isDateValid.h"
using namespace std;

struct Date
{
    int day, month, year, ref;
};

struct bankacc
{
    int day, month, yr;
    int accno;
    char name[30];
    int opbal;
};

struct transaction
{
    int day, month, yr;
    int accno;
    char name[30];
    int deposit, withdraw, balance;
};

struct record
{
    int day, mon, yr;
    int accno;
    char name[30];
    int balance;
};

void accept(bankacc *b, transaction *t, int no);
void sortdate(Date arr[], int n);
bool compare(const Date &d1, const Date &d2);

int main()
{
    ofstream txn, rec;
    // out.open("D:\\Programs\\Project - Copy\\Files\\master.bin", ios::binary);
    txn.open("D:\\Programs\\Project\\Files\\txn.bin", ios::binary);
    rec.open("D:\\Programs\\Project\\Files\\rec.bin", ios::binary);
    if(txn.is_open() == false || rec.is_open() == false)
    {
        cerr<<"Error: Cannot create file.\n";
        return 1;
    }

    int size, c = 0;
    do
    {
        if(c!=0) cout<<"Enter a valid number. The given number should be less than 5.\nEnter the number of accounts: ";
        else cout<<"Enter the number of accounts you want to enter: ";
        cin>>size;
        c++;
    } while (size > 5 || size <= 0);

    bankacc bk[size];
    transaction t[size];
    record r[size];

    accept(bk, t, size);

    txn.write((char *)&size, sizeof(int));
    rec.write((char *)&size, sizeof(int));

    for(int i=0; i<size; i++) 
    {
        txn.write((char *)&t[i], sizeof(transaction));

        r[i].accno = bk[i].accno;
        strcpy(r[i].name, bk[i].name);
        r[i].balance = bk[i].opbal;
        r[i].day = bk[i].day;
        r[i].mon = bk[i].month;
        r[i].yr = bk[i].yr;

        rec.write((char *)&r[i], sizeof(record));
    }
    rec.close();
    txn.close();
    return 0;
}


void accept(bankacc *b, transaction *t, int no)
{
    bankacc *bk;
    transaction *txn;
    char dt[20]; int i;

    for(i=0; i<no; i++)
    {
        int check=0;
        bk = (b + i);
        cout<<"Enter account "<<i+1<<" details: \n";

        do
        {
            if(check != 0) cout<<"Enter a valid date.\n";
            else cout<<"Enter the date of opening the account (dd-mm-yyyy or dd/mm/yyyy): ";
            cin>>dt;
            sscanf(dt, "%d%*c%d%*c%d", &bk->day, &bk->month, &bk->yr);
            check++;
        }while(!isDateValid(dt));

        cout<<"Enter account number: ";
        cin>>bk->accno;
        cout<<"Enter name: ";
        cin>>bk->name;
        cout<<"Enter opening balance: ";
        cin>>bk->opbal;
        cout<<"\n";
    }

    //Date sort:
    Date arr[no];
    for(i=0; i<no; i++)
    {
        bk = (b + i);
        arr[i] = {bk->day, bk->month, bk->yr, i};
    }

    int size = sizeof(arr)/sizeof(arr[0]);
    sortdate(arr, size);

    //Copy:
    for(i=0; i<no; i++)
    {
        bk = (b + arr[i].ref);
        txn = (t + i);

        txn->day = bk->day;
        txn->month = bk->month;
        txn->yr = bk->yr;
        txn->accno = bk->accno;
        strcpy(txn->name, bk->name);
        txn->deposit = txn->withdraw = 0;
        txn->balance = bk->opbal;
    }
}

void sortdate(Date arr[], int n)
{
    sort(arr, arr+n, compare); 
}

bool compare(const Date &d1, const Date &d2) 
{ 
    if (d1.year < d2.year) 
        return true; 
    if (d1.year == d2.year && d1.month < d2.month) 
        return true; 
    if (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day) 
        return true; 
  
    return false; 
} 