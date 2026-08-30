// BankExtension2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//




#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;


const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";



struct stUser
{
    string UserName;
    string Password;
    int Permissions;
    bool MarkForDelete = false;
};



stUser currentUser;


enum enTransactionsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eMainMenu = 4
};



enum enMainMenuChoice
{
    ShowClientsList = 1,
    eAddNewClient = 2,
    eDeletClient = 3,
    eUpdateClientInfo = 4,
    eFindClient = 5,
    eTransactionsMenueOptions = 6,
    eManageUsers = 7,
    eExit = 8
};


enum enMainMenuePermissions
{

    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTranactions = 32,
    pManageUsers = 64

};


enum enManageUsersMenueOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenue = 6

};



struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};


void ShowMainMenueScreen();
void GoBackToMainMenue();
short ReadNumber();


void GoBackToTransactoinsMenue();
short ReadTranactionsMenueOption();
void ShowTransactionsMenue();


void ShowManageUsersMenue();
short ReadManageUsersMenueOption();
void GoBackToManageMenue();
void Login();



vector <string> Splitstring(string DataLine, string Delim)
{
    vector<string> vWord;
    short pos = 0;
    string sWord;

    while ((pos = DataLine.find(Delim)) != std::string::npos)
    {
        sWord = DataLine.substr(0, pos);

        if (sWord != "")
        {
            vWord.push_back(sWord);
        }


        DataLine.erase(0, pos + Delim.length());

    }

    if (DataLine != "")
    {

        vWord.push_back(DataLine);

    }

    return vWord;

}

sClient ConvertLineDataToRectod(string DataLine, string Delim = "#//#")
{

    sClient Client;
    vector <string> vWord;

    vWord = Splitstring(DataLine, Delim);

    Client.AccountNumber = vWord[0];
    Client.PinCode = vWord[1];
    Client.Name = vWord[2];
    Client.Phone = vWord[3];
    Client.AccountBalance = stod(vWord[4]);

    return Client;

}

string ConvertRecordToDataLine(sClient Client, string Delim = "#//#")
{
    string DalaLine;

    DalaLine += Client.AccountNumber + Delim;
    DalaLine += Client.PinCode + Delim;
    DalaLine += Client.Name + Delim;
    DalaLine += Client.Phone + Delim;
    DalaLine += to_string(Client.AccountBalance);

    return DalaLine;
}

stUser ConvertUserLinetoRecord(string Line, string Delim = "#//#")
{
    vector <string> vUser;
    vUser = Splitstring(Line, Delim);

    stUser User;

    User.UserName = vUser[0];
    User.Password = vUser[1];
    User.Permissions = stoi(vUser[2]);

    return User;

}


string ConverUsertRecordToLine(stUser User, string Delim = "#//#")
{

    string Line;
    Line += User.UserName + Delim;
    Line += User.Password + Delim;
    Line += to_string(User.Permissions);

    return Line;

}

bool CheckAccessPermission(enMainMenuePermissions Permissions)
{
    if (currentUser.Permissions == enMainMenuePermissions::eAll)
    {
        return true;
    }


    if ((Permissions & currentUser.Permissions) == Permissions)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ShowAccessDeniedMessage()
{

    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this, \nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";

}

vector <sClient> LoadDataLineFromFileToVector(string FileName)
{
    fstream MyFile;
    vector <sClient> vClient;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string DataLine;
        sClient Client;

        while (getline(MyFile, DataLine))
        {

            Client = ConvertLineDataToRectod(DataLine);
            vClient.push_back(Client);

        }

        MyFile.close();
    }

    return vClient;
}

vector <stUser> LoadUserDataFromFileToVector(string FileName)
{
    vector <stUser> vUser;

    fstream MyFilel;

    MyFilel.open(FileName, ios::in);

    if (MyFilel.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFilel, Line))
        {

            User = ConvertUserLinetoRecord(Line);
            vUser.push_back(User);

        }

        MyFilel.close();

    }

    return vUser;

}



void PrintClientRecord(sClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowClientsScrren()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pListClients))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }



    vector <sClient> vClients;
    vClients = LoadDataLineFromFileToVector(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

bool ClientExistsByAccountNumber(string AccountNumber, string NameFile)
{

    fstream MyFile;
    MyFile.open(NameFile, ios::in);

    vector <sClient> vClinets;
    if (MyFile.is_open())
    {
        sClient Client;
        string DataLine;

        while (getline(MyFile, DataLine))
        {

            Client = ConvertLineDataToRectod(DataLine);


            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClinets.push_back(Client);

        }

        MyFile.close();

    }

    return false;

}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character

    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ? ";

        getline(cin >> ws, Client.AccountNumber);
    }



    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;


    return Client;
}

void AddNewClientToFile(string FileName, string DataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << DataLine << endl;
        MyFile.close();

    }

}

void AddNewClient()
{

    sClient Client;
    Client = ReadNewClient();
    AddNewClientToFile(ClientsFileName, ConvertRecordToDataLine(Client));

}

void AddNewClients()
{
    char Answer = 'y';

    do
    {

        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "Do You Want Add Ceint Y/N : ";
        cin >> Answer;


    } while (tolower(Answer) == 'y');

}


string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Enter Account Number  : ";
    cin >> AccountNumber;

    return AccountNumber;

}

void ShowAddNewClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "Add New Clien Screen";
    cout << "\n-----------------------------------\n\n";
    AddNewClients();
}

bool FoundClientByAccountNumber(string AccountNumber, sClient& Client, vector <sClient>& vClients)
{
    for (sClient& c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            Client = c;
            return true;
        }
    }

    return false;

}


void PrintClientCard(sClient Client)
{
    cout << "\n-----------------------------------\n";

    cout << "\nThe following are the client details:\n";
    cout << "\n-----------------------------------";

    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n\n";

}

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername    : " << User.UserName;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n-----------------------------------\n";
}


bool MarkClientDeletByAccuontNumber(string AccountNumber, vector <sClient>& vClienr)
{
    for (sClient& c : vClienr)

    {
        if (c.AccountNumber == AccountNumber)
        {
            c.MarkForDelete = true;
            return true;
        }
    }

    return false;

}

bool MarkUserDeleteByUserName(string UserName, vector<stUser>& vUsers)
{

    for (stUser& U : vUsers)
    {
        if (U.UserName == UserName)
        {

            U.MarkForDelete = true;
            return true;

        }
    }

    return false;
}

void SaveClientDataToFile(string FileName, vector <sClient>& vClinet)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        string DataLine;
        for (sClient& c : vClinet)
        {

            if (c.MarkForDelete == false)
            {
                DataLine = ConvertRecordToDataLine(c);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

}

void SaveUserDataToFile(string FileName, vector <stUser>& vUsers)
{


    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        string Line;
        for (stUser& U : vUsers)
        {
            if (U.MarkForDelete == false)
            {

                Line = ConverUsertRecordToLine(U);
                MyFile << Line << endl;

            }


        }

        MyFile.close();

    }
}

bool DeletClientByAccuntNumber(string AccountNumber, vector <sClient>& vClient)
{

    sClient Client;


    if (FoundClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);

        char Answer;
        cout << "\nDo you Want Delet Client  (" << Client.AccountNumber << ") : y/n : ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            MarkClientDeletByAccuontNumber(AccountNumber, vClient);
            SaveClientDataToFile(ClientsFileName, vClient);
            vClient = LoadDataLineFromFileToVector(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber
            << ") is Not Found!";
        return false;
    }

}

void  ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
    {

        ShowAccessDeniedMessage();
        GoBackToMainMenue();

        return;
    }



    cout << "\n-----------------------------------\n";
    cout << "Delet Client Screen";
    cout << "\n-----------------------------------\n\n";
    string AccountNuber;

    AccountNuber = ReadAccountNumber();

    vector <sClient> vClient;
    vClient = LoadDataLineFromFileToVector(ClientsFileName);
    DeletClientByAccuntNumber(AccountNuber, vClient);


}

sClient ChangeClientInfo(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}


bool UPDateClientByAccountNumber(string AccountNumber, vector <sClient>& vClient)
{
    sClient Client;

    if (FoundClientByAccountNumber(AccountNumber, Client, vClient))
    {
        PrintClientCard(Client);


        char Answer;
        cout << "\nDo you Want UPDate Client  (" << Client.AccountNumber << ") : y/n : ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            for (sClient& c : vClient)
            {
                if (c.AccountNumber == AccountNumber)
                {
                    c = ChangeClientInfo(AccountNumber);
                    SaveClientDataToFile(ClientsFileName, vClient);
                }
            }

            return true;
        }

    }
    else
    {

        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

        return false;
    }
}

void ShowUpDatClientScreen()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients))
    {

        ShowAccessDeniedMessage();
        GoBackToMainMenue();

        return;

    }



    cout << "\n-----------------------------------\n";
    cout << "UPDate Client Screen";
    cout << "\n-----------------------------------\n";
    string AccountNumber;
    AccountNumber = ReadAccountNumber();

    vector <sClient> vClient;
    vClient = LoadDataLineFromFileToVector(ClientsFileName);
    UPDateClientByAccountNumber(AccountNumber, vClient);

}

void ShowFindClientByAccountNumber()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pFindClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();

        return;
    }


    cout << "\n-----------------------------------\n";
    cout << "Find Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClient;
    vClient = LoadDataLineFromFileToVector(ClientsFileName);

    sClient Client;

    string AccountNumber;
    AccountNumber = ReadAccountNumber();

    if (FoundClientByAccountNumber(AccountNumber, Client, vClient))
    {

        PrintClientCard(Client);

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

    }

}




//________________________________________________________________________________

bool DepositBalanceToClientByAccountNumber(string AccountNuber, double Amount, vector <sClient>& vClient)
{

    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction?  y / n ? ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        for (sClient& c : vClient)
        {
            if (c.AccountNumber == AccountNuber)
            {
                c.AccountBalance += Amount;
                SaveClientDataToFile(ClientsFileName, vClient);
                cout << "\n\nDone Successfully. New balance is: "
                    << c.AccountBalance;
                return true;
            }
        }
    }
    else
    {
        return false;
    }

}

void ShowDepositScreen()
{

    cout << "\n-----------------------------------\n";
    cout << "\t\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    string AccountNumber;
    AccountNumber = ReadAccountNumber();

    vector<sClient> vClient;
    vClient = LoadDataLineFromFileToVector(ClientsFileName);
    sClient Client;

    while (!FoundClientByAccountNumber(AccountNumber, Client, vClient))
    {

        cout << "\nClient with [" << AccountNumber << "] does not  exist.\n";
        AccountNumber = ReadAccountNumber();

    }

    PrintClientCard(Client);
    double Amount;

    cout << " Please enter deposit amount ? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClient);

}


void ShowWithDrawScreen()
{

    cout << "\n-----------------------------------\n";
    cout << "\t\Draw Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients;
    vClients = LoadDataLineFromFileToVector(ClientsFileName);

    string AccountNumber = ReadAccountNumber();

    while (!FoundClientByAccountNumber(AccountNumber, Client, vClients))
    {

        cout << "\nClient with [" << AccountNumber << "] does not  exist.\n";
        AccountNumber = ReadAccountNumber();

    }

    PrintClientCard(Client);
    double Amount;

    cout << " Please enter Draw amount ? ";
    cin >> Amount;

    while (Client.AccountBalance < Amount)
    {

        cout << "\nAmount Exceeds the balance, you can withdraw upto : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;

    }


    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    double Total = 0;
    ShowClientsScrren();

    vector<sClient> vClient;

    vClient = LoadDataLineFromFileToVector(ClientsFileName);


    for (sClient& c : vClient)
    {

        Total += c.AccountBalance;

    }

    cout <<
        "\n\n\n\n\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << Total;

}

bool FindUserByUsername(string Username, vector <stUser> vUsers, stUser& User)
{


    for (stUser U : vUsers)
    {
        if (U.UserName == Username)
        {
            User = U;
            return true;
        }
    }

    return false;

}
bool FindUserByUserNameAndPassWord(string UserName, string PassWord, stUser& User)
{
    vector <stUser> vUser;
    vUser = LoadUserDataFromFileToVector(UsersFileName);

    for (stUser& c : vUser)
    {

        if (c.UserName == UserName && c.Password == PassWord)
        {
            User = c;
            return true;
        }

    }

    return false;
}
bool LoadUserInfo(string UserName, string PassWord)
{

    if (FindUserByUserNameAndPassWord(UserName, PassWord, currentUser))
        return true;
    else
        return false;

}
void PrintUserRecordLine(stUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permissions;
}
void ShowAllUsersScrren()
{

    vector <stUser> vUsers;
    vUsers = LoadUserDataFromFileToVector(UsersFileName);

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else
        for (stUser User : vUsers)
        {
            PrintUserRecordLine(User);
            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void AddUserToFile(string FileName, string Line)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << Line << endl;
        MyFile.close();

    }


}

bool UserExistsByUserName(string UserName, string FileName)
{

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    vector <stUser> vUsers;

    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {


            User = ConvertUserLinetoRecord(Line);
            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
            vUsers.push_back(User);

        }
        MyFile.close();

    }
    return false;

}


int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer;
    cout << "Do you want to give the user full access ? Y/N :  ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
        return -1;
    }

    cout << "\nDo you want to give the user access to :  \n";


    cout << "\nShow Clients List ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pListClients;

    }

    cout << "\nShow Add New Client ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pAddNewClient;

    }


    cout << "\nShow Delete Client ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pDeleteClient;

    }


    cout << "\nShow UPdate Client ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pUpdateClients;

    }

    cout << "\nShow Find Client ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pFindClient;

    }


    cout << "\nTranactions Client ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pTranactions;

    }


    cout << "\nManage User Client ? Y/N : ";
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {

        Permissions += enMainMenuePermissions::pManageUsers;

    }

    return Permissions;

}
stUser ReadNewUser()
{
    stUser User;

    cout << "Enter  UserName : ";
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.UserName);

    while (UserExistsByUserName(User.UserName, UsersFileName))
    {
        cout << "\User with [" << User.UserName << "] already exists, Enter another UserName ? : ";
        getline(cin, User.UserName);

    }

    cout << "\nEnter PAssWord : ";
    getline(cin, User.Password);


    User.Permissions = ReadPermissionsToSet();


    return User;

}

void AddNewUser()
{

    stUser User;
    User = ReadNewUser();
    AddUserToFile(UsersFileName, ConverUsertRecordToLine(User));


}


void AddNewUsers()
{
    char Answer;

    do
    {
        cout << "\nAdding New User:\n\n";

        AddNewUser();

        cout << " \nDo you want to add a new user ? Y/N : ";
        cin >> Answer;

    } while (tolower(Answer) == 'y');

}

void ShowAddNewUserScreen()
{

    cout << "\n-----------------------------------\n";
    cout << "\t\Add New User Screen";
    cout << "\n-----------------------------------\n";
    AddNewUsers();

}

bool DeleteUserByUserName(string UserName, vector <stUser>& vUsers)
{
    stUser User;

    if (FindUserByUsername(UserName, vUsers, User))
    {
        PrintUserCard(User);

        char Answer;
        cout << "\nDo you Want Delet User  (" << User.UserName << ") : y/n : ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {

            MarkUserDeleteByUserName(UserName, vUsers);
            SaveUserDataToFile(UsersFileName, vUsers);
            vUsers = LoadUserDataFromFileToVector(UsersFileName);
            cout << "\n\User Deleted Successfully.";

            return true;
        }
    }
    else
    {

        cout << "\USer with UserName (" << UserName << ") is Not Found!";
        return false;
    }
}

void ShowDeleteUserScreen()
{

    cout << "\n-----------------------------------\n";
    cout << "\t\Delete User Screen";
    cout << "\n-----------------------------------\n";


    vector <stUser> vUsers;

    vUsers = LoadUserDataFromFileToVector(UsersFileName);

    string UserName;
    cout << "\nEnter USerName : ";
    cin >> UserName;


    DeleteUserByUserName(UserName, vUsers);

}
stUser ChangeUserRecord(string Username)
{
    stUser User;

    User.UserName = Username;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadPermissionsToSet();
    return User;
}

bool UPDateUserByUserName(string UserName, vector <stUser>& vUsers)
{
    stUser User;

    if (FindUserByUsername(UserName, vUsers, User))
    {

        PrintUserCard(User);

        char Answer;

        cout << "Do you Want UpDat User  (" << User.UserName << ") : y/n : ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            for (stUser& U : vUsers)
            {
                if (U.UserName == UserName)
                {

                    U = ChangeUserRecord(UserName);
                    SaveUserDataToFile(UsersFileName, vUsers);

                    return true;
                }
            }

        }

    }
    else
    {
        cout << "\User with User (" << UserName << ") is Not Found!";
        return false;
    }



}

void ShowUPDateUserScreen()
{


    cout << "\n-----------------------------------\n";
    cout << "\t\UpDate User Screen";
    cout << "\n-----------------------------------\n";


    vector <stUser> vUsers;
    vUsers = LoadUserDataFromFileToVector(UsersFileName);


    string UserName;
    cout << "\nEnter USerName : ";
    cin >> UserName;

    UPDateUserByUserName(UserName, vUsers);

}

void ShowFindUserScreen()
{

    cout << "\n-----------------------------------\n";
    cout << "\t\Find User Screen";
    cout << "\n-----------------------------------\n";

    vector <stUser> vUsers;
    vUsers = LoadUserDataFromFileToVector(UsersFileName);


    string UserName;
    cout << "\nEnter USerName : ";
    cin >> UserName;

    stUser User;

    if (FindUserByUsername(UserName, vUsers, User))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "\nUser with UserName (" << UserName << ") is Not Found!";

    }

}

void PerfromManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOptions)
{
    switch (ManageUsersMenueOptions)
    {


    case enManageUsersMenueOptions::eListUsers:
    {

        system("cls");
        ShowAllUsersScrren();
        GoBackToManageMenue();

        break;

    }

    case enManageUsersMenueOptions::eAddNewUser:
    {

        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageMenue();

        break;

    }

    case enManageUsersMenueOptions::eDeleteUser:
    {

        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageMenue();

        break;

    }

    case enManageUsersMenueOptions::eUpdateUser:
    {

        system("cls");
        ShowUPDateUserScreen();
        GoBackToManageMenue();

        break;

    }

    case enManageUsersMenueOptions::eFindUser:
    {


        system("cls");
        ShowFindUserScreen();
        GoBackToManageMenue();

        break;

    }

    case enManageUsersMenueOptions::eMainMenue:
    {
        system("cls");
        ShowMainMenueScreen();

        break;
    }

    }
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOptions)
{
    switch (TransactionsMenueOptions)
    {

    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactoinsMenue();

        break;

    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactoinsMenue();

        break;

    }

    case enTransactionsMenueOptions::eTotalBalances:
    {

        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactoinsMenue();

        break;

    }

    case enTransactionsMenueOptions::eMainMenu:
    {
        system("cls");
        ShowMainMenueScreen();
        break;
    }



    }



}

void PerfromMainMenueOption(enMainMenuChoice MainMenuChoice)
{

    switch (MainMenuChoice)
    {


    case enMainMenuChoice::ShowClientsList:


    {
        system("cls");
        ShowClientsScrren();
        GoBackToMainMenue();

        break;
    }


    case enMainMenuChoice::eAddNewClient:
    {

        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenue();

        break;
    }

    case enMainMenuChoice::eDeletClient:
    {

        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();

        break;

    }

    case enMainMenuChoice::eUpdateClientInfo:
    {

        system("cls");
        ShowUpDatClientScreen();
        GoBackToMainMenue();

        break;
    }

    case enMainMenuChoice::eFindClient:
    {
        system("cls");
        ShowFindClientByAccountNumber();
        GoBackToMainMenue();

        break;
    }

    case enMainMenuChoice::eTransactionsMenueOptions:
    {
        system("cls");
        ShowTransactionsMenue();

        break;

    }

    case enMainMenuChoice::eManageUsers:
    {
        system("cls");
        ShowManageUsersMenue();

        break;

    }

    case enMainMenuChoice::eExit:
    {
        system("cls");
        Login();

        break;
    }

    }
}

void ShowMainMenueScreen()
{

    system("cls");
    cout << "\n===========================================================\n";

    cout << "                     Main Menu                         \n";

    cout << "===========================================================\n";

    cout << "\t\t[1] Show Client List\n";
    cout << "\t\t[2] Add New Client\n";
    cout << "\t\t[3] Delete Client\n";
    cout << "\t\t[4] Update Client Info\n";
    cout << "\t\t[5] Find Client\n";
    cout << "\t\t[6] Transaction\n";
    cout << "\t\t[7] Manage users\n";
    cout << "\t\t[8] Exit\n";

    cout << "===========================================================\n";

    PerfromMainMenueOption(enMainMenuChoice(ReadNumber()));
}

void GoBackToManageMenue()
{
    cout << "\n\nPress any key to go back to Manade Menue...";
    system("pause>0");
    ShowManageUsersMenue();
}

void GoBackToTransactoinsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}

void ShowTransactionsMenue()
{
    if (!CheckAccessPermission(enMainMenuePermissions::pTranactions))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();
        return;
    }

    system("cls");

    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";

    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTranactionsMenueOption());
}
void ShowManageUsersMenue()
{

    if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenue();

        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";

    PerfromManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
}

short ReadManageUsersMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadNumber()
{
    short Number;
    cout << "Choose what do you want to do? [1 to 8]? ";
    cin >> Number;

    return Number;
}

short ReadTranactionsMenueOption()
{
    short Number;
    cout << "Choose what do you want to do? [1 to 4]? ";
    cin >> Number;

    return Number;
}

void GoBackToMainMenue()
{

    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenueScreen();

}


void Login()
{

    bool LoginFaild = false;
    string Username, Password;

    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";


        if (LoginFaild)
        {

            cout << "Invlaid Username/Password!\n";

        }

        cout << "Enter Username? ";
        cin >> Username;

        cout << "Enter Password? ";
        cin >> Password;

        LoginFaild = !LoadUserInfo(Username, Password);

    } while (LoginFaild);



    ShowMainMenueScreen();


}

int main()
{
    Login();
}

