#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "isDateValid.h"
using namespace std;

struct transaction
{
    int day, month, yr;
    int accno;
    char name[30];
    int deposit, withdraw, balance;
};

struct record
{
    int day, mon, yr;   //Acc open date
    int accno;
    char name[30];
    int balance;
};

struct Date 
{ 
    int day, month, year, ref; 
}; 

void accept(transaction *ob, fstream &txn, fstream &rec, int no);
bool checkaccno(int chkaccno, int *accno, int limit);
int pos(int inp, int *accno);
bool compare(const Date &d1, const Date &d2);
void sortDates(Date arr[], int n);

int main()
{
    fstream t, r;
    t.open("Files\\txn.bin", ios::in | ios::out | ios::binary);
    r.open("Files\\rec.bin", ios::in | ios::out | ios::binary);

    if(!t.is_open() || !r.is_open())
    {
        cerr<<"Error: Cannot create file.\n";
        return 0;
    }
    
    int numrec, numtxn, i, k, c=0, no;
    do
    {
        if(c!=0) cout<<"Enter a number less than 5: ";
        else cout<<"Enter the number of withdrawal: ";
        cin>>no;
        c++;
    }while(no > 5 || no <= 0);
    transaction txn[no], *txnptr;

    accept(txn, t, r, no);

    r.seekg(ios::beg);
    t.seekg(ios::beg);
    r.read((char *)&numrec, sizeof(int));
    t.read((char *)&numtxn, sizeof(int));
    
    record rec[numrec], *recptr;
    r.seekg(sizeof(int), ios::beg);

    for(i=0; i<numrec; i++)
    {
        recptr = (rec + i);
        r.read((char *)recptr, sizeof(record));
    }

    for(i=0; i<numrec; i++)
    {
        recptr = (rec + i);
        for(k=0; k<numtxn; k++)
        {
            if(recptr->accno == txn[k].accno)
            {
                if(recptr->balance > txn[k].balance)    recptr->balance = txn[k].balance;
            }
        }
    }

    //Test:
    /*for(i=0; i<numrec; i++)
    {
        recptr = (rec + i);
        cout<<recptr->day<<"-"<<recptr->mon<<"-"<<recptr->yr<<" -> "<<recptr->accno<<" -> "<<recptr->name<<" -> "<<recptr->balance<<"\n";
    }*/

    r.close();
    remove("Files\\rec.bin");
    ofstream r1;
    r1.open("Files\\rec.bin", ios::binary);

    if(r1.is_open() == false)
    {
        cerr<<"Abnormal termination.\n";
        return 1;
    }

    r1.write((char *)&numrec, sizeof(int));
    for(i=0; i<numrec; i++)
    {
        recptr = (rec + i);
        r1.write((char *)recptr, sizeof(record));
    }

    c = numtxn + no;
    transaction t1[c], t2[c];
    t.seekg(sizeof(int), ios::beg);

    for(i=0; i<numtxn; i++)
    {
        txnptr = (t1 + i);
        t.read((char *)txnptr, sizeof(transaction));
    }

    k=0;
    for(i=0; i<c; i++)
    {
        t1[numtxn + i] = txn[k];
        k++;
    }

    //Sort Dates:
    Date arr[c];
    for(i=0; i<c; i++)
    {
        txnptr = (t1 + i);
        arr[i] = {txnptr->day, txnptr->month, txnptr->yr, i};
    }

    int n = sizeof(arr)/sizeof(arr[0]);
    sortDates(arr, n);

    for(i=0; i<c; i++)
    {
        txnptr = (t1 + arr[i].ref);
        t2[i].day = txnptr->day;
        t2[i].month = txnptr->month;
        t2[i].yr = txnptr->yr;
        t2[i].accno = txnptr->accno;
        strcpy(t2[i].name, txnptr->name);
        t2[i].deposit = txnptr->deposit;
        t2[i].withdraw = txnptr->withdraw;
        t2[i].balance = txnptr->balance;
    }

    t.close();
    remove("Files\\txn.bin");
    
    ofstream new_t;
    new_t.open("Files\\txn.bin", ios::binary);
    if(new_t.is_open() == false)
    {
        cerr<<"Abnormal termination.\n";
        return 1;
    }

    new_t.write((char *)&c, sizeof(int));

    for(i=0; i<c; i++)
    {
        txnptr = (t2 + i);
        new_t.write((char *)txnptr, sizeof(transaction));
    }

    new_t.close();
    r1.close();
    return 0;
}

void accept(transaction *ob, fstream &txn, fstream &rec, int no)
{
    transaction *txnptr;
    int day, mon, yr;
    int withdraw, numrec, i, k, c, loc;
    rec.read((char *)&numrec, sizeof(int));
    
    int accno[numrec], balance[numrec];
    char opendt[numrec][20], dt[no], name[30];

    //Get accno, opendates and current balance
    for(i=0; i<numrec; i++)
    {
        rec.read((char *)&day, sizeof(int));
        rec.read((char *)&mon, sizeof(int));
        rec.read((char *)&yr, sizeof(int));
        rec.read((char *)&accno[i], sizeof(int));
        rec.seekg(30*sizeof(char) + 2, ios::cur);
        rec.read((char *)&balance[i], sizeof(int));
        sprintf(opendt[i], "%d-%d-%d", day, mon, yr);
    }
    cout<<"Account numbers ad their last deposits: \n";
    for(i=0; i<numrec; i++) cout<<accno[i]<<" -> "<<opendt[i]<<"\n";

    //Accept details:
    for(i=0; i<no; i++)
    {
        txnptr = (ob + i);
        c = 0;
        do
        {
            if(c != 0) cout<<"Enter a valid account number: ";
            else cout<<"Enter account number: ";
            cin>>k;
            c++;
        }while(!checkaccno(k, accno, numrec));
        txnptr->accno = k;

        loc = pos(k, accno);

        c = 0;
        do
        {
            if(c!=0) cout<<"Enter a valid date (dd-mm-yyyy or dd/mm/yyyy): ";
            else cout<<"Enter withdrawal date (dd-mm-yyyy or dd/mm/yyyy): ";
            cin>>dt;
            c++;
        }while(!isDateValid(dt) || !isDateValid(dt, opendt[loc]));
        sscanf(dt, "%d%*c%d%*c%d", &txnptr->day, &txnptr->month, &txnptr->yr);

        c = 0;
        do
        {
            if(c!=0) cout<<"Invalid withdrawal amount.\nEnter Withdrawal amount: ";
            else cout<<"Enter withdrawal amount: ";
            cin>>withdraw;
            c++;
        }while(withdraw > balance[loc] || withdraw <=0);
        cout<<"\n";

        balance[loc] = balance[loc] - withdraw;
        txnptr->balance = balance[loc];
        txnptr->withdraw = withdraw;
        txnptr->deposit = 0;        
    }

    for(i=0; i<no; i++)
    {
        txnptr = (ob + i);
        loc = pos(txnptr->accno, accno);

        rec.seekg(sizeof(int), ios::beg);
        rec.seekg(loc*sizeof(record), ios::cur);
        rec.seekg(4*sizeof(int), ios::cur);
        rec.read((char *)&name, 30*sizeof(char));
        strcpy(txnptr->name, name);
    }
}

bool checkaccno(int chkaccno, int *accno, int limit)
{
    int i;
    for(i=0; i<limit; i++)
    {
        if(chkaccno == accno[i]){return true;}
    }
    return false;
}

int pos(int inp, int *accno)
{
    for(int i=0;;i++)
    {
        if(inp == accno[i]) return i;
    }
}

bool compare(const Date &d1, const Date &d2) 
{ 
    if (d1.year < d2.year) return true; 
    if (d1.year == d2.year && d1.month < d2.month) return true; 
    if (d1.year == d2.year && d1.month == d2.month && d1.day < d2.day) return true; 
    return false; 
}

void sortDates(Date arr[], int n) 
{
    sort(arr, arr+n, compare); 
}