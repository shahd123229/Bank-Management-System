#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<fstream>

using namespace std;

string delma = "#//#";
string ClientFileName = "clientsdata";
string UserFileName = "usersdata";

enum mainmenue {liste = 1, add = 2, del = 3, update = 4, findd = 5, transactions = 6 , manage = 7, logout = 8};
enum transactionmenue {deposit = 1, withdraw = 2, TotalBalances = 3,  mainscreen = 4};
enum enManageMenue {List = 1, Add = 2, Del = 3, Update = 4, Find = 5};

struct stClient{

string accn;
string code;
string name;
string phone;
double balance;
bool MarkToDel = false;
};


struct permission{

   bool show = 0, add = 0, del = 0, update = 0, Find = 0, transactions = 0, manage = 0;
};


struct stUser{

    string name;
    string password;
    short BinaryAccess = 0;
    bool MarkToDel = false;
    permission access;
} CurrentUser;


void MainMenue();
void transactionscreen();
void AddNewClient();
void Login();
void ManageUsersScreen();
void AddUser();


stClient ClientLineToRecord(string line){


  stClient c;

   short pos = line.find(delma);
   c.accn = line.substr(0, pos);
   line.erase(0, pos + delma.length());

   pos = line.find(delma);
   c.code = line.substr(0, pos);
   line.erase(0, pos + delma.length());

   pos = line.find(delma);
   c.name = line.substr(0, pos);
   line.erase(0, pos + delma.length());


   pos = line.find(delma);
   c.phone = line.substr(0, pos);
   line.erase(0, pos + delma.length());

   c.balance = stod(line);


   return c;

}

stUser UserLineToRecord(string line){

  stUser u;

  short pos = line.find(delma);
  string SWord = line.substr(0, pos);
  u.name = SWord;

  line.erase(0, pos + delma.length());

  pos = line.find(delma);
  SWord = line.substr(0, pos);
  u.password = SWord;

  line.erase(0, pos + delma.length());

  u.BinaryAccess = stoi(line);

  return u;
 }


vector <stClient> LoadClientDataFromFile(){

    stClient c;
   vector <stClient> vclient;

   fstream myfile;

   myfile.open(ClientFileName, ios::in);

   if(myfile.is_open()){

    string line;
    while(getline(myfile, line)){

     c = ClientLineToRecord(line);
     vclient.push_back(c);
    }
   }
   myfile.close();

   return vclient;
}

vector <stUser> LoadUserDataFromFile(){

   stUser u;
   vector <stUser> vUser;

   fstream myfile;

   myfile.open(UserFileName, ios::in);

   if(myfile.is_open()){

    string line;
    while(getline(myfile, line)){

     u = UserLineToRecord(line);
    vUser.push_back(u);

   }
   }
   myfile.close();

   return vUser;
}



void ShowClientData(stClient c){

      cout<<"\n\nThe following are client data ";
      cout<<"\n----------------------------------------\n";
      cout<<left<<setw(20)<<"Account number : "<<c.accn<<endl;
      cout<<left<<setw(20)<<"Pin Code : "<<c.code<<endl;
      cout<<left<<setw(20)<<"Name : "<<c.name<<endl;
      cout<<left<<setw(20)<<"Phone : "<<c.phone<<endl;
      cout<<left<<setw(20)<<"Balance Salary : "<<c.balance<<endl;
      cout<<"\n----------------------------------------\n\n";

}


void ShowAllClients(bool ShowTotalBalance=false){

  vector <stClient> vclient;
  vclient = LoadClientDataFromFile();
  system("cls");

  double AllBalances = 0;


  cout<<"                           Client List ("<<vclient.size()<<") Clients.";
  cout<<"\n______________________________________________________________________________________________________________\n\n";
  cout<<"| "<<setw(15)<<left<<"Acccount Number"<<"| "<<left<<setw(15)<<"Pin Code"<<"| "<<left<<setw(50)<<"Client Name";
  cout<<"| "<<left<<setw(15)<<"Phone"<<"| "<<left<<setw(15)<<"Balance";
  cout<<"\n______________________________________________________________________________________________________________\n";

  for(stClient &c : vclient){

    AllBalances = AllBalances + c.balance;

    cout<<"| "<<left<<setw(15)<<c.accn<<"| "<<left<<setw(15)<<c.code<<"| "<<left<<setw(50)<<c.name;
    cout<<"| "<<left<<setw(15)<<c.phone<<"| "<<left<<setw(15)<<c.balance<<endl;
  }

    cout<<"\n\n______________________________________________________________________________________________________________";


     if(ShowTotalBalance)
       cout<<"\n\n                 Total Balances = "<<AllBalances;

       cout<<"\nPress any key to go back to main menue...";
       system("pause>0");

}

string CheckRepeated(){

  vector <stClient> vclient;
  vclient = LoadClientDataFromFile();

  string accn;
  bool repeat;

  do{

    repeat = false;
   getline(cin>>ws, accn);

  for(stClient &cl : vclient){


    if(accn==cl.accn)
        {
     cout<<"\n\nClient with ["<<accn<<"] already exists, enter another Account Number? ";
     repeat = true;break;
        }

  }

  }while(repeat);

    return accn;
  }


string ClientRecordToLine(stClient c){

  string line = "";

  line = line + c.accn + delma;
  line = line + c.code + delma;
  line = line + c.name + delma;
  line = line + c.phone + delma;
  line = line + to_string(c.balance);

   return line;

}

string UserRecordToLine(stUser u){

  string line = "";

  line = line + u.name + delma;
  line = line + u.password + delma;
  line = line + to_string(u.BinaryAccess);

  return line;
}


void SaveClientsDataToFile(vector <stClient> vclient){

  fstream myfile;
  myfile.open(ClientFileName, ios::out);

  if(myfile.is_open()){

    string line;

    for(stClient &c : vclient)
{
     if(c.MarkToDel==false)
     {
        line = ClientRecordToLine(c);
        myfile<<line<<endl;
         }
}
  }
  myfile.close();
  }

void SaveUserDataToFile(vector <stUser> vUser){

  fstream myfile;
  myfile.open(UserFileName, ios::out);

  if(myfile.is_open()){

    string line;

    for(stUser &u : vUser)
{
     if(u.MarkToDel==false)
     {
        line = UserRecordToLine(u);
        myfile<<line<<endl;
         }
}
  }
  myfile.close();
}


void  AddNewClient(){

  vector <stClient> vclient = LoadClientDataFromFile();
  stClient c;
  system("cls");

  cout<<"------------------------------------";
  cout<<"\n      Add New Client Screen";
  cout<<"\n------------------------------------";
  cout<<"\nAdding New client : \n\n";

  cout<<"Enter Account Number? ";
  c.accn = CheckRepeated();

  cout<<"\nEnter Pin Code? ";
  getline(cin, c.code);

  cout<<"\nEnter Name? ";
  getline(cin, c.name);

  cout<<"\nEnter Phone? ";
  getline(cin, c.phone);

  cout<<"Enter Account Balance? ";
  cin>>c.balance;

   vclient.push_back(c);
   SaveClientsDataToFile(vclient);

  char ans;
  cout<<"\n\nthe new client is added succesfully...do you want to add more new clients? (y/n)";
  cin>>ans;
    if(tolower(ans)=='y')
    AddNewClient();
}

void  DeleteClient(){

   vector <stClient> vclient;
   vclient = LoadClientDataFromFile();

   system("cls");

  string accn;
  char ans;


  cout<<"------------------------------------";
  cout<<"\n      Delete Client Screen";
  cout<<"\n------------------------------------";

   cout<<"\n\nEnter Account Number? ";
   getline(cin>>ws, accn);

   for(stClient &c : vclient){

    if(c.accn==accn){
        ShowClientData(c);

      cout<<"are you sure do you want to delete this client? (y/n) ";
      cin>>ans;

      if(tolower(ans)=='y')
        {
        c.MarkToDel = true;
        SaveClientsDataToFile(vclient);
        cout<<"\n\nClient Deleted successfully.";
        cout<<"\npress any key to go to main menue...";
        system("pause>0");
        return;
        }
    }}

    cout<<"the client with ("<<accn<<") account number is not found!";
    cout<<"\npress any key to go to main menue...";
   system("pause>0");

  }


stClient Editclient(string accn){

  stClient c;

  c.accn = accn;

  cout<<"\n\nEnter Pin Code : ";
  getline(cin>>ws, c.code);

  cout<<"\nEnter Name : ";
  getline(cin>>ws, c.name);

  cout<<"\n\nEnter Phone : ";
  getline(cin>>ws, c.phone);

  cout<<"\n\nEnter Account Balance : ";
  cin>>c.balance;

  return c;

}



void  UpdateClientData(){

  vector <stClient> vclient;
  vclient = LoadClientDataFromFile();

  system("cls");

  string accn;
  char ans;

  cout<<"-------------------------------------------";
  cout<<"\n              Update Client Screen         ";
  cout<<"\n-------------------------------------------\n\n";
  cout<<"please enter account number? ";
  cin>>accn;

   for(stClient &c : vclient){

    if(c.accn==accn){

        ShowClientData(c);

      cout<<"are you sure you want to update this client data? y/n? ";
      cin>>ans;

      if(tolower(ans)=='y')
      {

       c =  Editclient(accn);
       SaveClientsDataToFile(vclient);
       cout<<"Press any key to go back to main menue...";
       system("pause>0");return;
      }

}}
     cout<<"\nthe account number ("<<accn<<") is not found!";
      cout<<"\nPress any key to go back to main menue...";
       system("pause>0");
}


stClient PerformTransaction(stClient c, double Amount){

    c.balance = c.balance + Amount;

    return c;
}



void Deposit(){

  system("cls");

  vector <stClient> vclient;
  vclient = LoadClientDataFromFile();

  cout<<"---------------------------------";
  cout<<"\n         Deposit Screen";
  cout<<"\n--------------------------------";

     string accn;
    char ans;
    double DepositAmount;

    while(true){
        cout<<"\nPlease enter Account Number? ";
         getline(cin>>ws, accn);

      for(stClient &c : vclient){

        if(c.accn==accn)
          {
              ShowClientData(c);

    cout<<"\nPlease enter deposit amount? ";
    cin>>DepositAmount;

    cout<<"\nAre you sure you want to perform this transaction? y/n? ";
    cin>>ans;

    if(tolower(ans)=='y'){
        c =  PerformTransaction(c, DepositAmount);
        SaveClientsDataToFile(vclient);

       cout<<"\n\nThis transaction done successfully..";}
       else return;
      cout<<"Press any key to go back to transaction menu...";
       system("pause>0");return;
     }
     }
        cout<<"\nThe client with ("<<accn<<") account number is not found!";
     }
}

double CheckAmount(stClient c){


 double withdraw;
 cout<<"please enter withdraw amount? ";


 while(true){

    cin>>withdraw;

     if(withdraw>c.balance)

      cout<<"\n\nAmount Exceeds the balance, you can withdraw up to : "<<c.balance<<"\nplease enter another amount?";

    else

        return withdraw;
 }
}

void  Withdraw(){


  system("cls");

  vector <stClient> vclient;
  vclient = LoadClientDataFromFile();

  cout<<"---------------------------------";
  cout<<"\n         Withdraw Screen";
  cout<<"\n--------------------------------";

  string accn;
  double WithdrawAmount;
  char ans;

  while(true){


  cout<<"\nplease enter Account Number? ";
  getline(cin>>ws, accn);

  for(stClient &c : vclient){


      if(c.accn==accn){

        ShowClientData(c);
        WithdrawAmount = CheckAmount(c);

        cout<<"\n\nare you sure you want to perform this transaction? y/n? ";
        cin>>ans;

          if(tolower(ans)=='y'){
                c = PerformTransaction(c, WithdrawAmount*(-1));
                SaveClientsDataToFile(vclient);
                cout<<"\nthis transaction done successfully..";
                 }

       cout<<"Press any key to go back to transaction menue...";
       system("pause>0");return;
  }
  }
  cout<<"\nthe client with account number ("<<accn<<") is not found!";


}}

void ALLBalances(){


  ShowAllClients(true);

}



void ReadTransactionChoice(){

 int choice;
 cin>>choice;

 switch (choice){

 case transactionmenue::deposit:
     Deposit();
     transactionscreen();
     break;


 case transactionmenue::withdraw:
     Withdraw();
     transactionscreen();
     break;

 case transactionmenue::TotalBalances:
     ALLBalances();
     transactionscreen();
     break;

 case transactionmenue::mainscreen:
     MainMenue();
     break;

 default:
    cout<<"\ninvalid choice!!!";
    MainMenue();
  }
}



void transactionscreen(){

   system("cls");

  cout<<"=======================================";
  cout<<"\n      Transactions Menu Screen";
  cout<<"\n====================================";
  cout<<"\n         [1] Deposit.";
  cout<<"\n         [2] Withdraw.";
  cout<<"\n         [3] Total Balances.";
  cout<<"\n         [4] Main Menue.";
  cout<<"\n====================================";
  cout<<"\nChoose what do you want to do? [1 to 4]?";

  ReadTransactionChoice();

}

void  FindClient(){

  vector <stClient> vclient;
  vclient = LoadClientDataFromFile();

  system("cls");

  string accn;

  cout<<"-------------------------------------------";
  cout<<"\n              Find Client Screen         ";
  cout<<"\n-------------------------------------------\n\n";
  cout<<"please enter account number? ";
  cin>>accn;

   for(stClient &c : vclient){

    if(c.accn==accn){
       ShowClientData(c);

       cout<<"Press any key to go back to main menue...";
       system("pause>0");return;


}}
     cout<<"\nthe account number ("<<accn<<") is not found!";
      cout<<"\nPress any key to go back to main menue...";
       system("pause>0");
}

void ShowAllUsers(){

  vector <stUser> vUser;
  vUser = LoadUserDataFromFile();

  system("cls");

    cout<<"                           Users List ("<<vUser.size()<<") Users.";
  cout<<"\n______________________________________________________________________________________________________________\n\n";
  cout<<"| "<<setw(15)<<left<<"User Name"<<"| "<<left<<setw(15)<<"Password"<<"| "<<left<<setw(50)<<"Permissions\n";
  cout<<"\n______________________________________________________________________________________________________________\n";

  for(stUser &u : vUser){

    cout<<"| "<<left<<setw(15)<<u.name<<"| "<<left<<setw(15)<<u.password<<"| "<<left<<setw(50)<<u.BinaryAccess<<endl;
  }

    cout<<"\n\n______________________________________________________________________________________________________________";


       cout<<"\nPress any key to go back to Manage Menue...";
       system("pause>0");

}

void ShowUserData(stUser u, bool End = true){

  cout << "\n\nThe Following Are The User Details:";
  cout << "\n-------------------------------------\n";
  cout << "UserName     : " << u.name << endl;;
  cout << "Password     : " << u.password <<endl;
  cout << "Permissions  : " << u.BinaryAccess;
  cout << "\n-------------------------------------\n";

  if(End){
    cout<<"\nPress any key to go back to Manage Menue...";
    system("pause>0");
  }

}

void FindUser(){

  vector <stUser> vUser;
  vUser = LoadUserDataFromFile();

  system("cls");

  string UserName;

  cout<<"-------------------------------------------";
  cout<<"\n              Find Client Screen         ";
  cout<<"\n-------------------------------------------\n\n";
  cout<<"please enter UserName? ";
  cin>>UserName;

   for(stUser &u : vUser){

      if(UserName==u.name){
        ShowUserData(u);
        return;
        }
}

    cout << "\nInvalide UserName!";
    cout<<"\nPress any key to go back to Manage Menue...";
    system("pause>0");
}

bool CheckUsernameRepeat(string name){

  vector <stUser> vUser;
  vUser = LoadUserDataFromFile();

  for(stUser &u : vUser){

    if(name==u.name)
      {
        cout << "\n\nUser with [" << u.name << "] already exists, Enter Another Username? ";
        return true;
      }
  }

  return false;
}

void ApplyPermissionsFromBinary(stUser &u){

  u.access.show = (u.BinaryAccess & 1);
  u.access.add = (u.BinaryAccess & 2);
  u.access.del = (u.BinaryAccess & 4);
  u.access.update = (u.BinaryAccess & 8);
  u.access.Find = (u.BinaryAccess & 16);
  u.access.transactions = (u.BinaryAccess & 32);
  u.access.manage = (u.BinaryAccess & 64);

}

stUser UserPermissions(stUser u){

    char choice;
    u.BinaryAccess = 0;
    cout << "Do you want to give access to : \n\n";
    cout << "Show client list? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 1);
    }

    cout << "\n\nAdd new client? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 2);
    }

    cout << "\n\nDelete client? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 4);
    }

    cout << "\n\nUpdate client? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 8);
    }

    cout << "\n\nFind client? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 16);
    }

    cout << "\n\nTransactions? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 32);
    }

    cout << "\n\nManage Users? y/n? ";
    cin >> choice;
    if(tolower(choice)=='y'){
      u.BinaryAccess = (u.BinaryAccess  | 64);
    }

    return u;


}

void AddUser(){

  stUser NewUser;
  vector <stUser> vUser;
  vUser = LoadUserDataFromFile();


  cout << "Adding New User: \n\n";
  cout << "Enter UserName? ";

  while(true){

    cin >> NewUser.name;
    if(!CheckUsernameRepeat(NewUser.name))
        break;
  }

  cout << "Enter Password? ";
  cin >> NewUser.password;

  char ans;
  cout << "\n\nDo you want to give Full Access? y/n? ";
  cin >> ans;

  if(tolower(ans)=='y'){
    NewUser.BinaryAccess = -1;
  }

  else
     NewUser = UserPermissions(NewUser);

  vUser.push_back(NewUser);
  SaveUserDataToFile(vUser);

  cout << "\nUser Added Sucessfully, do you want to add more users? y/n? ";
  cin >> ans;

  if(tolower(ans)=='y')
    AddUser();

}

void AddNewUser(){

  system("cls");
  cout << "-------------------------------------\n";
  cout << "          Add New User Screen\n";
  cout << "-------------------------------------\n";

  AddUser();

  cout << "Press Any Key To go Back to Manage Menue...";
  system("pause>0");
}



void DeleteUser(){

  vector <stUser> vUser;
  vUser = LoadUserDataFromFile();
  string username;
  char ans;
  bool UserFound = false;

  system("cls");
  cout << "-------------------------------------\n";
  cout << "          Delete User Screen\n";
  cout << "-------------------------------------\n";

  cout << "Please enter Username? ";
  cin >> username;

  for(stUser &u : vUser){

    if(username=="Admin"){
      cout << "\nYou cannot Delete or Update Admin.";
      UserFound = true;
      break;
    }
    if(CurrentUser.name==username)
    {
      cout << "\nYou cannot Delete or Update Yourself, Contact your Admin.";
      UserFound = true;
      break;
    }

    if(username==u.name)
    {
        ShowUserData(u, false);
        UserFound = true;
        cout << "\n\nAre you sure you want delete this User? y/n? ";
        cin >> ans;
        if(tolower(ans)=='y')
        {
            u.MarkToDel = true;
            SaveUserDataToFile(vUser);
            cout << "\nUser is deleted Succesfully...";
        }
        else break;
    }
  }

   if(!UserFound)
     cout << "\nUser with Username [" << username << " is not found!";

   cout << "\n\nPress Any Key To go Back to Manage Menue...";
   system("pause>0");
}

stUser UpdateUserData(stUser u){

    char ans;
    ShowUserData(u, false);

    cout << "Are you sure you want to update this user? y/n? ";
    cin >> ans;

    if(tolower(ans)=='y'){

       cout << "\nEnter Password? ";
       cin >> u.password;

       cout << "\n\nDo you want to give Full Access? y/n? ";
       cin >> ans;

       if(tolower(ans)=='y')
         u.BinaryAccess = -1;

       else
        u = UserPermissions(u);
    }

    return u;
}


void UpdateUser(){

  vector <stUser> vUser;
  vUser = LoadUserDataFromFile();
  string username;
  bool IsFound = false;

  system("cls");
  cout << "-------------------------------------\n";
  cout << "          Update User Screen\n";
  cout << "-------------------------------------\n";
  cout << "Enter Username? ";
  cin >> username;

  for(stUser &u : vUser){

      if(CurrentUser.name!="Admin" && username=="Admin"){
         cout << "\nYou cannot Update or Delete Admin.";
         IsFound = true;
         break;
      }

      if(username==CurrentUser.name && CurrentUser.BinaryAccess!=-1){
         cout << "\nYou cannot Update your self, Contact your Admin.";
         IsFound = true;
         break;
      }

      if(u.name==username){
        u = UpdateUserData(u);
        SaveUserDataToFile(vUser);
        cout << "\nUser Data Updated Succesfully.";
        IsFound = true;
     }
  }

   if(!IsFound)
    cout << "\nUser with Username [" << username << "] is not found!";

   cout << "\n\nPress Any Key To go Back to Manage Menue...";
   system("pause>0");
}

void ReadManageUsersChoice(short choice){

  switch(choice){

    case enManageMenue::List:
         ShowAllUsers();
         ManageUsersScreen();
         break;

    case enManageMenue::Add:
         AddNewUser();
         ManageUsersScreen();
         break;

    case enManageMenue::Del:
         DeleteUser();
         ManageUsersScreen();
         break;


    case enManageMenue::Update:
         UpdateUser();
         ManageUsersScreen();
         break;

    case enManageMenue::Find:
         FindUser();
         ManageUsersScreen();
         break;

    default:
        MainMenue();

  }

}

void ManageUsersScreen(){

    short choice;
    system("cls");

    cout<<"===========================================";
    cout<<"\n        Manage Users Menue Screen";
    cout<<"\n===========================================";
    cout<<"\n         [1] List Users.";
    cout<<"\n         [2] Add New User.";
    cout<<"\n         [3] Delete User.";
    cout<<"\n         [4] Update User.";
    cout<<"\n         [5] Find User.";
    cout<<"\n         [6] Main Menue.";;
    cout<<"\n===========================================";
    cout<<"\nchoose what do you want to do? [1 to 6]? ";

    cin>>choice;
    ReadManageUsersChoice(choice);

}

void AccessDenied(){

  system("cls");

  cout << "----------------------------------------\n";
  cout << "Access Denied,";
  cout << "\nYou don't Have Permission To Do This,";
  cout << "\nPlease Contat Your Admin.\n";
  cout << "----------------------------------------\n\n\n";
  cout << "Press Any Key To go Back to Manage Menue...";
  system("pause>0");
}



void ReadMainMenueChoice(int choice){

switch (choice){

     case mainmenue::liste:
          if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.show)
             ShowAllClients();
          else
            AccessDenied();

             MainMenue();
             break;

     case mainmenue::add:
        if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.add)
            AddNewClient();
        else
            AccessDenied();

         MainMenue();
         break;

     case mainmenue::del:
        if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.del)
            DeleteClient();
        else
            AccessDenied();

         MainMenue();
         break;

     case mainmenue::update:
        if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.update)
            UpdateClientData();
        else
            AccessDenied();

         MainMenue();
         break;


     case mainmenue::findd:
        if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.Find)
            FindClient();
        else
            AccessDenied();

         MainMenue();
         break;

    case mainmenue::transactions:
        if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.transactions)
            transactionscreen();
        else
            AccessDenied();

         MainMenue();
        break;

    case mainmenue::manage:
        if(CurrentUser.BinaryAccess==-1 || CurrentUser.access.manage)
            ManageUsersScreen();
        else
            AccessDenied();
         MainMenue();
        break;

     case mainmenue::logout:
         Login();
         break;

     default:
        MainMenue();
}
}

void MainMenue(){

    int choice;
    system("cls");

    cout<<"===========================================";
    cout<<"\n        Main Menue Screen";
    cout<<"\n===========================================";
    cout<<"\n         [1] Show Client List.";
    cout<<"\n         [2] Add New Client.";
    cout<<"\n         [3] Delete Client.";
    cout<<"\n         [4] Update Client Info.";
    cout<<"\n         [5] Find Client.";
    cout<<"\n         [6] Transactions.";
    cout<<"\n         [7] Manage Users.";
    cout<<"\n         [8] Logout.";
    cout<<"\n===========================================";
    cout<<"\nchoose what do you want to do? [1 to 8]? ";
    cin>>choice;

    ReadMainMenueChoice(choice);
}

bool CheckUser(){

   vector <stUser> vUser;
   vUser = LoadUserDataFromFile();

   string UserName, password;
   bool IsFound = false;

   do{

   cout<<"\nEnter UserName? ";
   cin>>UserName;
   cout<<"Enter Password? ";
   cin>>password;

   for(stUser &u : vUser){

     if(u.name==UserName && u.password==password){
        CurrentUser = u;
        ApplyPermissionsFromBinary(CurrentUser);
        return true;
        }
   }
     cout << "\nInvalid UserName/Password, Press Any Key To try again...";
     system("pause>0");
     Login();

   }while(!IsFound);

}

void Login(){

  system("cls");
  cout<<"-----------------------------";
  cout<<"\n         Login Screen      ";
  cout<<"\n-----------------------------\n";

   if(CheckUser())
     MainMenue();
}


int main(){

    Login();

    system("pause>0");
}
