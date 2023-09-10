#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

class Bank_Account{
    int account_number;
    char name[50];
    char type;
    int Money_Deposit;

public:
   
    void modify();
    void report() const;
    int retacno() const{
        return account_number;
    }
    void dep(int x){
        Money_Deposit+=x;
    }
    void draw(int x){
        Money_Deposit-=x;
    }
    int retdeposit() const{
        return Money_Deposit;
    }
    void create_account();
    void Display_Account();

};
void Bank_Account:: report() const{
    cout<<account_number<<setw(10)<<" "<<name<<setw(10)<<type<<setw(6)<<Money_Deposit<<endl;
}

void Bank_Account::modify(){
    cout<<"\t Account Number: "<<account_number<<endl;
    cout<<"|t Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Modify Type of Account: ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Modify Balance Amount: ";
    cin>>Money_Deposit;
}
void write_account();  //function to write record in binary file
void display_details(int); //function to display account details given by user
void delete_account(int);  //function to delete record of file
void display_all(); //function to display all account details
void money_deposit_withdraw(int,int);
void Updation_bank_account(int);


void Bank_Account::create_account(){
    system("cls");
    cout<<"\t Enter the account number: ";
    cin>>account_number;
    cout<<"\t Enter the na,e of account holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Enter the type of account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount (>=500 for Saving and >=1000 for current): ";
    cin>>Money_Deposit;
    cout<<endl;
    cout<<"\t Account Created.... :)";
    cout<<endl;


}
void Bank_Account::Display_Account(){
    cout<<"\t Bank Account Number: "<<account_number<<endl;
    cout<<"\t Account Holder Name: "<<name<<endl;
    cout<<"\t Type of Account: "<<type<<endl;
    cout<<"\t Balance amount: "<<Money_Deposit<<endl;

}

int main(){
    char ch;
    int num;

    do{

    cout<<"\t\t ----------------------------------------"<<endl;
    cout<<"\t\t | Welcome to the Bank Management System |"<<endl;
    cout<<"\t\t ----------------------------------------"<<endl;

    cout<<endl;
    cout<<"\t --- Main Menu ---"<<endl;
    cout<<"\t 1. Create Account"<<endl;
    cout<<"\t 2. Deposit Money"<<endl;
    cout<<"\t 3. Withdraw Money"<<endl;
    cout<<"\t 4. Balane Enquiry"<<endl;
    cout<<"\t 5. All Account Holder List"<<endl;
    cout<<"\t 6. Close an Account"<<endl;  
    cout<<"\t 7. Modify an Account"<<endl;
    cout<<"\t 8. Exit"<<endl;
    cout<<endl;

    cout<<"\t Enter your choice (1-8): ";
    cin>>ch;

    switch(ch){
        case '1':
            write_account();
            break;
        case '2':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            money_deposit_withdraw(num,1);     //deposit function
            break;      
        case '3':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
             money_deposit_withdraw(num,2);       //withdraw function
            break;
        case '4': 
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            display_details(num);      //balance enquiry function
            break;   
        case '5':    
            display_all();              //display all function
            break;
        case '6':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            delete_account(num);          //close account function
            break;
        case '7':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            Updation_bank_account(num);                               //modify account function
            break;
        case '8':
        cout<<"/t Thanks for using the Bank Management System"<<endl;
        break;   
    }    
    cin.ignore();
    cin.get();
    }while(ch!='8');
    return 0;

    // Bank_Account B;
    // B.create_account();
    // cout<<endl;
    // B.Display_Account();
    // return 0;  
}

void write_account() //function to write record in binary file
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
    outFile.close();

}

void delete_account(int n){
    Bank_Account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! Press any key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);

    while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account))){
        if(ac.retacno()!=n){
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
        }
    }
    inFile.close();
    outFile.close();
    remove("Bank_Account.dat");
    rename("Temp.dat", "Bank_Account.dat");
    cout<<"\t Record Deleted..."<<endl;
}

void display_details(int n){
    Bank_Account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! Press any key...";
        return;
    }
    cout<<"\t Bank Account Details"<<endl;
     while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account))){
        if(ac.retacno()==n){
            ac.Display_Account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false){
        cout<<"\t Account Number does not exist"<<endl;
    }
    

}


void display_all(){
    system("cls");
    Bank_Account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! Press any key...";
        return;
    }
    cout<<"\t Bank Account Holder List"<<endl;
    cout<<"==================================================="<<endl;
    cout<<"A/c no.         NAME          TYPE          BALANCE"<<endl;
    cout<<"==================================================="<<endl;
    while(inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank_Account))){
        ac.report();
    }
    inFile.close();
}

void money_deposit_withdraw(int n, int  option){

    int amt;
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be open || Press any key...";
        return;
    }
    while(!File.eof() && found==false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if(ac.retacno()==n){
            ac.Display_Account();
            if(option==1){
                cout<<"\t Enter the amount to be deposited: ";
                cin>>amt;
                
                ac.dep(amt);
            }
            if(option==2){
                cout<<"\t Enter the amount to be withdraw: ";
                cin>>amt;
                int balance = ac.retdeposit()-amt;
                if(balance<0){
                    cout<<"\t Insufficient balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos=(-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
            cout<<"\t Record Updated"<<endl;
            found=true;

        }
    }
    File.close();
    if(found==false){
        cout<<"\t Record Not Found"<<endl;
    }

}

void Updation_bank_account(int x){
    bool found=false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be open || Press any key...";
        return;
    }
    while(!File.eof() && found==false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if(ac.retacno()==x){
            ac.Display_Account();
            cout<<endl;
            cout<<"\t Enter the new details of the account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank_Account));
            cout<<"\t Record Updated"<<endl;
            found=true;
                
        }      
    }
    File.close();
    if(found==false){
        cout<<"\t Record Not Found"<<endl;
    }

}






