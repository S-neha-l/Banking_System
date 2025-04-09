#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    char ch;
    system("cls");
    system("compileall.cmd");
    while(true)
    {
        cout<<"__________________________________________________________________\n\n\n";
        cout<<"1. Create an account file (destroys all current files).\n";
        cout<<"2. Deposit.\n";
        cout<<"3. Withdraw.\n";
        cout<<"4. Read all transaction history.\n";
        cout<<"5. Read transaction history of given account number.\n";
        cout<<"6. View the total balance of all account holders. \n";
        cout<<"7. Exit.\n";
        cout<<"Enter your choice: ";
        cin>>ch;

        if(ch == '1'){ system("cls"); system("master.exe"); }
        else if(ch == '2'){ system("cls"); system("deposit.exe"); }
        else if(ch == '3'){ system("cls"); system("withdraw.exe"); }
        else if(ch == '4'){ system("cls"); system("readtxn.exe"); }
        else if(ch == '5'){ system("cls"); system("usertxn.exe"); }
        else if(ch == '6'){ system("cls"); system("readrec.exe"); }
        else if(ch == '7'){ system("cls"); break; }
        else {system("cls"); cout<<"Invalid input.\n"; }
        cout<<"\n\n";
    }
}