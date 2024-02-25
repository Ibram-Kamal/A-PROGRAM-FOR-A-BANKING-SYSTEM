#include <iostream>
#include <limits>
#include <string.h>
using namespace std;
class ATM;
int accounts_counter=0;
int account_number_occurnces = 0;
int option;
bool sending_fail = 0;
bool retry_send_amount=0;
int get_option();
double get_input_double();
bool check_account_name(char[]);
bool already_exist_number (int [],ATM []);
class ATM {
private :
    char Account_name[100];
    int Card_number [10];
    double Amount ;
public :
    void create_new_account(ATM []);
    void Deposit();
    void Withdrawal();
    void Transfer(bool,double);
    void Print_acc_data();
    bool Card_number_compare(int []);   //compares an int array to the object card number
};
void ATM:: create_new_account (ATM a[])
{
  if (accounts_counter < 100)
  {
  int check;
  int check_counter=0;
  retry_account_name:
  cout <<"Enter account name:  ";
  cin.ignore(0,'n');
  cin.getline(Account_name,100);
  cin.clear();
  if (!check_account_name(Account_name))
  {
      cout << "Invalid account name(only letters and spaces allowed),try again.  "<<endl;
      goto retry_account_name;
  }
  cin.clear();
  retry_card_number:
  cout <<"Enter the card number(10 numbers each separated by space): ";
    bool is_space = 1;
    char possible_card_number_1[1000]={NULL};
    char possible_card_number_2[1000]={NULL};
    int counter = 0;
    int spaces_counter_1 = 0;
    int spaces_counter_2 = 0;
    cin.getline(possible_card_number_1,1000);
    for(int i =0;i<1000;i++)
        {
         if(possible_card_number_1[i]== NULL)
         {
             if(possible_card_number_1[i-1]==' ')
                spaces_counter_1--;
         }
         if(possible_card_number_1[i]==' ')
        {
            spaces_counter_1++;
        }
        if(possible_card_number_1[i]!=' ')
        {

            if((spaces_counter_2!=spaces_counter_1)&&counter!=0)
            {
                 possible_card_number_2[counter]=' ';
                 counter ++;
            }
            possible_card_number_2[counter]=possible_card_number_1[i];
            counter ++;
            spaces_counter_2= spaces_counter_1;
        }
        }
if(spaces_counter_1 != 9)
{
    cout << "Invalid,you must enter only 10 numbers(from 0 to 9) each separated by a space "<<endl; //error when the number of spaces that user entered is less than 9
    goto retry_card_number;
}
if(strlen(possible_card_number_2)!=19)
{
    cout << "you must enter only 10 numbers(from 0 to 9) each separated by a space "<<endl; //error if the user did not enter exactly 19 characters
    goto retry_card_number;
}
else
{
int check;
int number_of_spaces=0;
for (int i = 0;i<19;i++)
{
    check =  possible_card_number_2[i];
    if(check==32)
    {
        is_space = 1;
        number_of_spaces++;
    }
    else
    {
        if(is_space == 1)
        {
        Card_number[i-number_of_spaces]=check-'0';
        is_space = 0;
        if(Card_number[i-number_of_spaces]>9|| Card_number[i-number_of_spaces]<0)
        {
          cout << "Invalid card number,please try again(only numbers from 0 to 9 separated by a space) "<<endl; //error if user entered any character except number
          cin.clear();
          goto retry_card_number;
        }
        }
        else
        {
            cout << "You must enter 10 number ,each separated by a space."<<endl; //error if the user did not enter the number in the right sequence of one number then one space and so on
            goto retry_card_number;
        }
    }
}
}

  check =Card_number[0];
  check_counter = 0;
  for (int i =0 ; i<10;i++)
    {
        check = Card_number[i];
        if (check == Card_number[0])
            check_counter++;
    }
    if (check_counter==10)
    {
        cout << "Invalid card number(easy to guess) ,please try again.  "<<endl; //error if user entered same number ten times in card numbers
        check_counter = 0;
        goto retry_card_number;
    }
    if(already_exist_number(Card_number,a))
    {
        cout << "Account number already exists,please insert a different number."<<endl; //error if user entered a card number that exists
        goto retry_card_number;
    }
  }
  else
  {
      cout << "Account list is full"<<endl; //error if the object list is full
  }
}
void ATM::Deposit()
{
  double new_deposit;
  cout << "Enter the amount to Deposit(enter 0 to exit): ";
  new_deposit = get_input_double();
  new_deposit+=new_deposit*.01;
  Amount+=new_deposit;
}
void ATM::Withdrawal()
{
  double amount_to_withdraw;
  retry_withdraw:
  cout << "Enter the amount to Withdraw(enter 0 to exit): ";
  amount_to_withdraw = get_input_double();
  amount_to_withdraw+=amount_to_withdraw*.03;
  if (amount_to_withdraw <= Amount)
  Amount-=amount_to_withdraw;
  else
    {
     cout << "Withdraw failed, no enough money in account,try again"<<endl;
     goto retry_withdraw;
    }
}
void ATM::Transfer(bool send_or_receive,double transfer_amount)
{
  if(send_or_receive)
  {
      transfer_amount+=transfer_amount*.015;
      if (transfer_amount <= Amount)
     {
      Amount-=transfer_amount;
      sending_fail=0;
      retry_send_amount=0;
      }
      else
      {
          if(Amount!=0)
            retry_send_amount=1;
          cout << "Transfer failed, no enough money in account."<<endl;
          sending_fail = 1;
          return;
      }
  }
  else
  {
      if(!sending_fail)
      {
      transfer_amount-=transfer_amount*.015;
      Amount+=transfer_amount;
      }
      else
        sending_fail = 0 ;
  }
}
void ATM::Print_acc_data()
{
  cout<<"----------------"<<endl;
  cout <<"Account name : "<< Account_name<<endl;
  cout <<"Card number  : ";
  for (int i=0;i<10;i++)
   cout << Card_number[i];
  cout <<endl;
  cout <<"The amount   : "<< Amount<<endl;
}

bool ATM::Card_number_compare(int key[]) //compare the object card number with a specific card number
{
    for(int i=0;i<10;i++)
    {  if(Card_number[i]!= key[i])
          return 0;
       if(i==9)
         {
          return 1;
         }
    }
}
bool already_exist_number (int possible_number[],ATM a[]) //check if the card number is unique
{
 for (int j=0;j<100;j++)
 {
      if(a[j].Card_number_compare(possible_number))
      {
          account_number_occurnces++;
      }
 }
 if(account_number_occurnces > 1)
      {
          account_number_occurnces = 0;
          return 1;
      }
 account_number_occurnces = 0;
 return 0;
}
bool check_account_name(char possible_account_name[]) //check if the account name is only letters and spaces
{
  int check;
  if(strlen(possible_account_name)==0)
    return false;
  for(int i = 0;i<strlen(possible_account_name);i++)
  {
      check = possible_account_name[i];
      if(!((check>64&&check<91)||(check>96&&check<123)||((check == 32)&& i!=0)))
      {
       return false;
      }
  }
  return true;
}
int get_option() //check if the option is an int
{
    retry_get_option:
    char possible_number_1[1000]={NULL};
    cin.getline(possible_number_1,1000);
    if((possible_number_1[1]!=NULL || possible_number_1[0]==NULL))
    {
        cout<<"Invalid input ,please enter only one number: "; //error if the user did not enter in the option any number or more than one
        goto retry_get_option;
    }
    else
    {
        int check;
        check = possible_number_1[0]-'0';
        if (check > 9|| check < 0)
        {
            cout<<"Invalid input ,please enter only one number: "; //error if the user entered in the option any character except numbers
            goto retry_get_option;
        }
        return check;
    }

}

double get_input_double() //check if the (amount,sending_amount,etc) is a double
{
    double input ;
    cin >> input ;
    while (!cin.good() || input < 0 || cin.peek()!='\n')
    {
        cout << "Invalid number , please try again:  ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin >> input ;
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return input ;
}
void menu()//to show the options
{
    option = 0;
    cout<<"----------------"<<endl;
    cout << "1---Create new account"<<endl;
    cout << "2---Deposit"<<endl;
    cout << "3---transfer to another account"<<endl;
    cout << "4---withdrawal"<<endl;
    cout << "5---exit"<<endl;
    cout<<"----------------"<<endl;
    cout << "Please enter the number of operation (only one number): ";
    option = get_option();
}
int search_accounts(ATM a[])//search the object list for an object with a specific card number
{
    retry_key:
    if(option!=3)
        cout <<"Enter the card number(10 numbers each separated by space): ";
    bool is_space = 1;
    char possible_card_number_1[1000]={NULL};
    char possible_card_number_2[1000]={NULL};
    int key[10]={0};
    int counter = 0;
    int spaces_counter_1 = 0;
    int spaces_counter_2 = 0;
    cin.getline(possible_card_number_1,1000);
    for(int i =0;i<1000;i++)
        {
         if(possible_card_number_1[i]== NULL)
         {
             if(possible_card_number_1[i-1]==' ')
                spaces_counter_1--;
         }
         if(possible_card_number_1[i]==' ')
        {
            spaces_counter_1++;
        }
        if(possible_card_number_1[i]!=' ')
        {

            if((spaces_counter_2!=spaces_counter_1)&&counter!=0)
            {
                 possible_card_number_2[counter]=' ';
                 counter ++;
            }
            possible_card_number_2[counter]=possible_card_number_1[i];
            counter ++;
            spaces_counter_2= spaces_counter_1;
        }
        }
if(spaces_counter_1 != 9)
{
    cout << "Invalid,you must enter only 10 numbers(from 0 to 9) each separated by a space: "; //error when the number of spaces that user entered is less than 9
    if(option!=3)
        cout<<endl;
    goto retry_key;
}
if(strlen(possible_card_number_2)!=19)
{
    cout << "you must enter only 10 numbers(from 0 to 9) each separated by a space: "; //error if the user did not enter exactly 19 characters
    if(option!=3)
        cout<<endl;
    goto retry_key;
}
else
{
int check;
int number_of_spaces=0;
for (int i = 0;i<19;i++)
{
    check =  possible_card_number_2[i];
    if(check==32)
    {
        is_space = 1;
        number_of_spaces++;
    }
    else
    {
        if(is_space == 1)
        {
        key[i-number_of_spaces]=check-'0';
        is_space = 0;
        if(key[i-number_of_spaces]>9|| key[i-number_of_spaces]<0)
        {
          cout << "Invalid card number,please try again(only numbers from 0 to 9 separated by a space): "; //error if user entered any character except number

          cin.clear();
          goto retry_key;
        }
        }
        else
        {
            cout << "You must enter 10 number ,each separated by a space:"; //error if the user did not enter the number in the right sequence of one number then one space and so on
            if(option!=3)
                cout<<endl;
            goto retry_key;
        }
    }
}
}
for(int j =0;j<100;j++)
   {
      if (a[j].Card_number_compare(key))
        return j;
   }
   cout << "Account number not found."<<endl; //error if the entered card number is not in the object list
   return -1;
}
int main()
{
ATM a[100];
    do{
        menu();
        if (option==1)
        {
          a[accounts_counter].create_new_account(a);
          a[accounts_counter].Print_acc_data();
          accounts_counter ++;
        }
        else if (option==2)
        {
        if(accounts_counter>=1){
          int target_account;
          retry_deposit:
          target_account=search_accounts(a);
          if(target_account!=-1&&target_account<accounts_counter)
          {
            cin.clear();
            a[target_account].Deposit();
            a[target_account].Print_acc_data();
          }
          else
            goto retry_deposit;}
        else
        {
             cout<<"Invalid Deposit operation"<<endl;
            cout<<"To use Deposit operation you first have to create one account at least"<<endl;
        }
        }
        else if (option==3)
        {
            if(accounts_counter>=2){
            int sender_account;
            int receiver_account;
            double amount_to_send;
            retry_transfer_sender:
            cout << "Please enter the number of the sending account(10 numbers each separated by space)  :";
            sender_account= search_accounts(a);
            if (sender_account>=0&&sender_account<accounts_counter)
            {
            retry_transfer_receiver:
            cout << "Please enter the number of the receiving account(10 numbers each separated by space):";
            receiver_account=search_accounts(a);
            if (sender_account!=receiver_account && receiver_account>=0&&receiver_account<accounts_counter)
            {
             do{cout <<"Enter the amount to send:  ";
             amount_to_send = get_input_double();
             a[sender_account].Transfer(1,amount_to_send);}while(retry_send_amount);
             a[receiver_account].Transfer(0,amount_to_send);
             cout<<"Sending Account:"<<endl;
             a[sender_account].Print_acc_data();
             cout<<"Receiving Account:"<<endl;
             a[receiver_account].Print_acc_data();
            }
            else
            {
                cout << "Invalid transfer operation,please choose two different (existing) numbers."<<endl;
                goto retry_transfer_receiver;
            }
            }
            else
            {
                cout << "Invalid transfer operation,please choose an existing number."<<endl;
                goto retry_transfer_sender;
            }
        }
        else{
            cout<<"Invalid Transfer operation"<<endl;
            cout<<"To use Transfer operation you first have to create two accounts at least"<<endl;
        }}
        else if (option==4)
        {
        if(accounts_counter>=1){
          int target_account;
          retry_withdraw:
          target_account=search_accounts(a);
          if(target_account!=-1&&target_account<accounts_counter)
          {
            a[target_account].Withdrawal();
            a[target_account].Print_acc_data();
          }
          else
              goto retry_withdraw;}
        else
        {
             cout<<"Invalid Withdraw operation"<<endl;
            cout<<"To use Withdraw operation you first have to create one account at least"<<endl;
        }
        }
        else if (option==5)
        {
            return 0 ;
        }
        else
        {
            cout << "Invalid operation ,please enter a valid operation number."<<endl;
            option = 0;
        }
if (option==1)
    {
        cin.clear();
    }

    }while(1);
}
