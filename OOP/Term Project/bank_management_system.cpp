/**
 * BANK MANAGEMENT SYSTEM
 * TERM PROJECT
 * AUTHOR: BSCLMR259021 
 *
 * *** NOTE : PREFERABLE TO RUN ON LINUX DUE TO MINGW NOT SUPPOTING SOME LIBRARIES IN THE SOURCE CODE ***
 * **  HOW TO RUN ON WINDOWS SYSTEMS**
 * 1. Open Command prompt
 *
 * 2. Navigate to folder containing bank_management_system.cpp i.e cd C:\Users\HP\Desktop\"Term Project"\bank_management_system.cpp
 *
 * 3. compile the source folder with -std=c++11 compiler option i.e g++ -std=c++11 bank_management_system.cpp
 *
 * 4. Run the compiled source file i.e a.exe
 *
 * **  HOW TO RUN ON LINUX SYSTEMS**
 * 1. Open your default terminal e.g bash
 *
 * 2. Navigate to folder containing bank_management_system.cpp i.e cd /home/david/Desktop/OOP/bank_management_system.cpp
 *
 * 3. compile the source folder with -std=c++11 compiler option i.e g++ -std=c++11 bank_management_system.cpp
 *
 * 4. Run the compiled source file i.e ./a.out
 */


#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define LENGTH 8
#define ATTEMPTS 3

/* Macro for clearing screen on windows and linux systems*/
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif        

string tempAccountNumber;

string generateTransactionCode();
string generateAccountNumber();
int randomNumber(int from, int end);
int randomLetter(int from, int end);
double cost(double amount);
void mainMenu();
void customerRegistration();
void customerRegistrationConfigurationFile();
string flag(string fileName);
void customerLogin();
bool pinAccountNumberSearch(string field1, string field2);
void account();
void deposit();
void withdraw();
void sendMoney();
void accountInfo();
void changePin(string accNumber);
void removeAccount(string accNumber);
void logout();
void accountConfigurationFile();
double total(string accountNumber);
bool accountNumberSearch(string field1);
void miniStatement(string accountNumber);
void printSpaces(int numberOfSpaces);
int countRecords(string fileName);
int validIntegerInput(int begin, int end);


int main(){
    system(CLEAR);
    mainMenu();
    return 0;
}


// generate transaction code
string generateTransactionCode(){
    srand(time(NULL));
    string tCode = "xxxxxxxx";
    int index = 0;
    for (int codeLength=0; codeLength<LENGTH; ++codeLength){
        if (codeLength <= 4){
            tCode.at(index) = int(randomLetter(65, 90));
        } else {
            if (codeLength % 2 > 0){
                tCode.at(index) = int(randomNumber(48, 57));
            } else {
                tCode.at(index) = int(randomLetter(65, 90));
            }
        }
        index += 1;
    }
    return tCode;
}


// generate account number
string generateAccountNumber(){
    srand(time(NULL));
    string accountNumber = "00000000";
    string temp1, temp2;
    int index = 0;
    for (int accountNumberLength=0; accountNumberLength<LENGTH; ++accountNumberLength){
        accountNumber.at(index) = int(randomNumber(48, 57));
        index += 1;
    }
    cout << "Your account number is: " << accountNumber << endl;
    return accountNumber;
}


// generate random number
// for linux
/*
char randomNumber(){
    std::random_device random_num_generator;
    std::uniform_int_distribution<int> int_distribution(48,57);
    int result = int_distribution(random_num_generator);
    return result;
}
*/


// for windows
int randomNumber(int from, int end){
    int number;
    number = rand() % end + from;
    while(number > end){
        number = rand() % end + from;
    }
    return number;
}


// generate random letter
// Linux
/*
char randomLetter(){
    std::random_device random_num_generator;
    std::uniform_int_distribution<int> int_distribution(65,90);
    int result = int_distribution(random_num_generator);
    return result;
}
*/

// for windows
int randomLetter(int from, int end){
    int letter;
    letter = rand() % end + from;
    while(letter > end){
        letter = rand() % end + from;
    }
    return letter;
}

// Calculate the cost of a transaction
double cost(double amount){
    double tCost = 0;

    if (amount <= 100){
        tCost = 0;
    } else if (amount <= 500) {
        tCost = 30;
    } else if (amount <= 1000){
        tCost = 60;
    } else if (amount <= 1500){
        tCost = 90;
    } else if (amount > 1500){
        tCost = 150;
    }
    return tCost;
}


// Dashboard
void mainMenu(){
    int option;
    cout << ":: Main Menu ::\n[1] Register\n[2] Login\n[3] Exit" << endl;
    cout << "Select Your Option [1 - 3] > ";
    option = validIntegerInput(1,2);
    if (option == 1){
        system(CLEAR);
        customerRegistrationConfigurationFile();
    } else if (option == 2){
        system(CLEAR);
        customerLogin();
    } else {
        cout << "Exiting ... " << endl;
        exit(0);
    }
}


// Create and Open CustomerRegistrationFile
void customerRegistration(){
    std::vector<string> fileRecord;
    string record;
    string value = flag("CustomerRegistrationConfigurationFile.txt"); // check the value stored in configuration file
        
    if (value != "true"){
        std::ofstream customerRegistration("CustomerRegistrationFile.bms", ios::app);
    }
    cout << ":: PLEASE FILL THE FOLLOWING FIELDS ::\n";
    cout << "1. First Name                  : "; cin >> record;
    fileRecord.push_back(record); 
    cout << "2. Last Name                   : "; cin >> record;
    fileRecord.push_back(record);  
    cout << "3. Email Address               : "; cin >> record;
    fileRecord.push_back(record); 
    cout << "4. Phone Number                : "; cin >> record;
    fileRecord.push_back(record);  
    cout << "5. Id Number                   : "; cin >> record;
    fileRecord.push_back(record); 
    cout << "6. Your preffered pin          : "; cin >> record;
    fileRecord.push_back(record);    
    record = generateAccountNumber();
    fileRecord.push_back(record);

    std::ofstream customerRegistration("CustomerRegistrationFile.bms", ios::app);
    if (customerRegistration.is_open()){
        customerRegistration << endl;
        customerRegistration << fileRecord[0] << "   " << fileRecord[1] << "   " << fileRecord[2] << "   " << fileRecord[3] << "   " << fileRecord[4] << "   " << fileRecord[5] << "   " << fileRecord[6] << endl;
        system(CLEAR);
        cout << "Your account number is " << record << endl;
        mainMenu();
    } else {
        cout << "could not open file" << endl;
    }    
}


// To apply some logic into knowing when to open/create CustomerRegistrationFile
void customerRegistrationConfigurationFile(){
    // check if config file exists
    std::ifstream fileCheck("CustomerRegistrationFile.bms");
    std::ofstream session;
    session.open ("CustomerRegistrationConfigurationFile.txt");
    if (session.is_open()) {
        if (fileCheck.is_open()){
            session << "true" << endl;
        }
        else {
            session << "false" << endl;
        }
        
    } else {
        cout << "file could not be opened" << endl;
    }
    customerRegistration(); // check the value stored in the configuration file
}


// checking the value stored in ConfigurationFile
string flag(string fileName){
    string value;
    std::ifstream configurationFile(fileName);
    if (configurationFile.is_open()){
        getline(configurationFile, value);
    } else {
        cout << "could not open file" << endl;
    }
    return value;
}


// authentication for a customer before account access
void customerLogin(){
    string accountNumber, pin;
    int attempts = 0;
    bool flagCredentials;
    while (true){
        cout << ":: PLEASE FILL THE FOLLOWING FIELDS ::" << endl;
        cout << "Account Number: ";
        cin >> accountNumber;
        cout << "PIN           : ";
        cin >> pin;
        flagCredentials = pinAccountNumberSearch(pin,accountNumber);
        if (flagCredentials == false){
            system(CLEAR);
            cout << "Invalid login credentials" << endl;
            ++ attempts;
            if (attempts == ATTEMPTS){
                system(CLEAR);
                cout << "Try again later .. " << endl;
                mainMenu();
            }
        } else {
            tempAccountNumber = accountNumber;
            system(CLEAR);
            accountConfigurationFile();
            account(); // display account menu 
            break;
        }
    }
}


// search for pin and account number in file record
bool pinAccountNumberSearch(string field1, string field2){
    string fName, lName, emailAddress, phoneNumber, idNumber, pin, accountNumber;
    bool rightCredentials = false;
    string tempRecord;
    std::ifstream recordSearch("CustomerRegistrationFile.bms");
    if (recordSearch.is_open()){
        while(getline(recordSearch, tempRecord)){
            recordSearch >> fName >> lName >> emailAddress >> phoneNumber >> idNumber >> pin >> accountNumber;
            if ((field1 == pin) && (field2 == accountNumber)){
                rightCredentials = true;
                break;
            } else {
                rightCredentials = false;
            }
        }
    } else {
        cout << "could not open file" << endl;
    }
    recordSearch.close();
    return rightCredentials;
}


// Account
void account(){
    int option;
    std::vector<string> fileRecord;
    string record;
    string value = flag("accountConfigurationFile.txt"); // check the value stored in configuration file
        
    if (value != "true"){
        std::ofstream customerRegistration("AccountFile.bms", ios::app);
    }

    cout << ":: Account Menu ::" << endl;
    cout << "[1] Deposit\n[2] Withdraw\n[3] Send Money\n[4] Account Info\n[5] Change PIN\n[6] Remove account\n[7] Logout" << endl;
    cout << "Select Your OPtion [1-7] > ";
    option = validIntegerInput(1,7);
    
    while (true){
        switch(option){
        case 1: system(CLEAR); deposit(); break;
        case 2: system(CLEAR); withdraw(); break;
        case 3: system(CLEAR); sendMoney(); break;
        case 4: system(CLEAR); accountInfo(); break;
        case 5: system(CLEAR); changePin(tempAccountNumber); break;
        case 6: system(CLEAR); removeAccount(tempAccountNumber); break;
        case 7: system(CLEAR); logout(); break;
        default: 
            system(CLEAR);
            cout << "invalid option!" << endl; 
            account();
        }
    }  
}


// To apply some logic into knowing when to open/ create AccountFile
void accountConfigurationFile(){
    // check if config file exists
    std::ifstream fileCheck("AccountFile.bms");
    std::ofstream session;
    session.open ("accountConfigurationFile.txt");
    if (session.is_open()) {
        if (fileCheck.is_open()){
            session << "true" << endl;
        }
        else {
            session << "false" << endl;
        }
        
    } else {
        cout << "file could not be opened" << endl;
    }

    account(); // check the value stored in the configuration file
}


//deposit
void deposit(){
    std::ofstream accountUpdate("AccountFile.bms", ios::app);
    double amount, serviceFee, newBalance;
    string transactionCode = generateTransactionCode();
    cout << "Enter Amount: ";
    cin >> amount;
    serviceFee = cost(amount);
    newBalance = amount - serviceFee;
    if (accountUpdate.is_open()){
        cout << transactionCode <<". Ksh." << serviceFee << " has been deducted from your account as a service fee. Ksh." << newBalance << " has been sent to your account. Your new balance is Ksh." << total(tempAccountNumber) + newBalance << endl;
        accountUpdate << endl;
        accountUpdate << tempAccountNumber << "    " << newBalance << "    " << transactionCode << "    " << "Deposit    -    0" <<  endl;
        account();
    } else {
        cout << "could not open file" << endl;
    }
    accountUpdate.close();
}


//logout
void logout(){
    system(CLEAR);
    mainMenu();
}


double total(string accountNumber){
    std::ifstream recordSearch("AccountFile.bms");
    double amount=0, cumulativeAmount = 0, sentAmount=0;
    string accNumber, transactionCode, tempRecord, transaction, recipient;
    if (recordSearch.is_open()){
        while(getline(recordSearch, tempRecord)){
            recordSearch >> accNumber >> amount >> transactionCode >> transaction >> recipient >> sentAmount;
            if (accountNumber == accNumber){
                cumulativeAmount += amount;
            } else if (accountNumber == recipient){
                cumulativeAmount += sentAmount;
            } else {
                continue;
            }
        }
    } else {
        cout << "could not open file" << endl;
    }
    recordSearch.close();
    
    // remove duplicate values in amount and sent amount
    if (amount > 0){
        cumulativeAmount -= amount;
    } else {
        cumulativeAmount -= sentAmount;
    }
    return cumulativeAmount;
}


// withdraw
void withdraw(){
    std::ofstream accountUpdate("AccountFile.bms", ios::app);
    double amount, serviceFee, newBalance;
    cout << "Enter Amount: ";
    cin >> amount;
    system(CLEAR);
    while(amount > total(tempAccountNumber)){
        cout << "You do not have enough cash in your account. Your current balance is Ksh." << total(tempAccountNumber) << endl;
        cout << "Enter Amount: ";
        cin >> amount;
    }
    string transactionCode = generateTransactionCode();
    serviceFee = cost(amount);
    newBalance = total(tempAccountNumber) - (amount - serviceFee); // calculate balance
    if (accountUpdate.is_open()){
        system(CLEAR);
        cout << transactionCode <<". Ksh." << serviceFee << " has been deducted from your account as a service fee.";
        cout << "you've withdrawn ksh." << amount << ". Your new balance is Ksh." << newBalance << endl;
        accountUpdate << endl;
        accountUpdate << tempAccountNumber << "    " << - (amount - serviceFee) << "    " << transactionCode << "    " << "Withdraw    -    0" << endl;
        account();
    } else {
        cout << "could not open file" << endl;
    }
    accountUpdate.close();
}


//send money
void sendMoney(){
    std::ofstream accountUpdate("AccountFile.bms", ios::app);
    string accountNumber;
    double amount, serviceFee, newBalance, sentAmount;
    cout << "Enter account Number: ";
    cin >> accountNumber;
    cout << "Enter Amount:         ";
    cin >> amount;
    bool flagAcccountNumber = accountNumberSearch(accountNumber);
    while (!flagAcccountNumber){
        system(CLEAR);
        cout << "The Account number doesn't exist, check and try again" << endl;
        sendMoney();
    }
    
    while(amount > total(tempAccountNumber)){
        system(CLEAR);
        cout << "Unsuccessful. You do not have enough cash in your account. Your current balance is Ksh." << total(tempAccountNumber) << endl;
        cout << "Enter Amount: ";
        cin >> amount;
    }
    string transactionCode = generateTransactionCode();
    serviceFee = cost(amount);
    newBalance = total(tempAccountNumber) - (amount - serviceFee); // calculate balance
    sentAmount = amount - serviceFee;
    if (accountUpdate.is_open()){
        system(CLEAR);
        cout << transactionCode <<". Ksh." << serviceFee << " has been deducted from your account as a service fee.";
        cout << "Successful. you've sent ksh." << sentAmount << " to " << accountNumber << ". Your new balance is Ksh." << newBalance << endl;
        accountUpdate << endl;
        accountUpdate << tempAccountNumber << "    " << - (amount - serviceFee) << "    " << transactionCode << "    " << "Sent" << "    "  << accountNumber << "    " << sentAmount << endl;
        account();
    } else {
        cout << "could not open file" << endl;
    }
    accountUpdate.close();
}

bool accountNumberSearch(string field1){
    string fName, lName, emailAddress, phoneNumber, idNumber, pin, accountNumber;
    bool rightCredentials = false;
    string tempRecord;
    std::ifstream recordSearch("CustomerRegistrationFile.bms");
    if (recordSearch.is_open()){
        while(getline(recordSearch, tempRecord)){
            recordSearch >> fName >> lName >> emailAddress >> phoneNumber >> idNumber >> pin >> accountNumber;
            if (field1 == accountNumber){
                rightCredentials = true;
                break;
            } else {
                rightCredentials = false;
            }
        }
    } else {
        cout << "could not open file";
    }
    recordSearch.close();
    return rightCredentials;
}


// account info
void accountInfo(){
    int option;
    double balance = total(tempAccountNumber);
    system(CLEAR);
    cout << "Balance: " << balance << endl;
    cout << "---------------------------------------------\n"; 
    printSpaces(7);
    cout << ":: Ministatement ::" << endl;
    cout << "Code";printSpaces(6);cout << "amount";printSpaces(6);cout << "Type";printSpaces(6);cout << "Recipient";printSpaces(6);cout<<"Sent" << endl;
    
    miniStatement(tempAccountNumber);
    account();
}


// Get the ministatement of the customer
void miniStatement(string accountNumber){
    std::ifstream recordSearch("AccountFile.bms");
    double amount;
    string accNumber, transactionCode, transactionType, recipient, amountSent;
    string tempRecord;

    if (recordSearch.is_open()){
        while (getline(recordSearch, tempRecord)){
            recordSearch >> accNumber >> amount >> transactionCode >> transactionType >> recipient >> amountSent;
            if (accountNumber == accNumber){
                cout << transactionCode;
                printSpaces(6);
                cout << amount;
                printSpaces(6);
                cout << transactionType;
                printSpaces(6);
                cout << recipient;
                printSpaces(6);
                cout << amountSent << endl;
            } else {
                continue;
            }
        }
    } else {
        cout << "File could not be opened" << endl;
    }
}


// print spaces
void printSpaces(int numberOfSpaces){
    string space;
    for (int i=0; i < numberOfSpaces; ++i){
        cout << "  ";
    }
}


// change pin
void changePin(string accNumber){
    string fName, lName, emailAddress, phoneNumber, idNumber, pin, accountNumber, newPin;
    string tempRecord;
    std::ifstream changePin("CustomerRegistrationFile.bms");
    std::ofstream tempFile;
    tempFile.open("temp.bms",ios::app);
    cout << "Enter new pin: ";
    cin >> newPin;

    // cache pin change before permanent storage
    if (changePin.is_open()){
        while (getline(changePin, tempRecord)){
            changePin >> fName >> lName >> emailAddress >> phoneNumber >> idNumber >> pin >> accountNumber;
            if(accNumber == accountNumber){
                pin = newPin;
                if (tempFile.is_open()){
                    tempFile << endl;
                    tempFile << fName << "    " << lName << "    " << emailAddress << "    " << phoneNumber << "    " << idNumber << "    " << pin << "    " << accountNumber << endl; 
                } else {
                    cout << "could not open file" << endl;
                }
            } else {
                tempFile << endl;
                tempFile << fName << "    " << lName << "    " << emailAddress << "    " << phoneNumber << "    " << idNumber << "    " << pin << "    " << accountNumber << endl; 
            }
        }
    } else {
        cout << "could not open file" << endl;
    }
    changePin.close();
    tempFile.close();

    // reflect pin change in the main database
    // remove Cached file
    if (remove("CustomerRegistrationFile.bms") != 0){
        cout << "Error changing pin" << endl;
    } else {
        cout << "Changing pin ... " << endl;
    }

    std::ofstream finalPinChange;
    std::ifstream permFile("temp.bms");
    finalPinChange.open("CustomerRegistrationFile.bms", ios::app);
    
    if (permFile.is_open()){
        int count = 0;
        while (count < (countRecords("temp.bms")-1)){
            getline(permFile, tempRecord);
            finalPinChange << endl;
            finalPinChange << tempRecord;
            ++ count;
        }
        cout << "Successful, your new pin is, " << newPin << endl;
    } else {
        cout << "could not open file" << endl;
    }

    finalPinChange.close();
    permFile.close();
    if (remove("temp.bms") != 0){
        cout << "Error changing pin" << endl;
    } else {
        cout << "done ... " << endl;
    }
    account();
}


// return the number or records in a file
int countRecords(string fileName){
    int totalRecords = 0;
    string tempRecord;
    std:: ifstream count(fileName);
    if (count.is_open()){
        while (getline(count, tempRecord)){
        ++ totalRecords;
        }
    } else {
        cout << "Problem counting records";
    }
    return totalRecords;
}


//Deactivate account
void removeAccount(string accNumber){
    double totalBalance = total(accNumber);
    string transactionCode = generateTransactionCode();

    string fName, lName, emailAddress, phoneNumber, idNumber, pin, accountNumber;
    string tempRecord;
    char option = 'n';

    std::ifstream removeAccount("CustomerRegistrationFile.bms");
    std::ofstream tempFile;
    tempFile.open("temp.bms",ios::app);

    while (true){
        cout << "Are you sure you want to remove your account!(y/n): ";
        cin >> option;

        if (option == 'y'){
            // cache account details before permanent removal
            if (removeAccount.is_open()){
                while (getline(removeAccount, tempRecord)){
                    removeAccount >> fName >> lName >> emailAddress >> phoneNumber >> idNumber >> pin >> accountNumber;
                    if(accNumber == accountNumber){
                        pin = "XXXXXXXX";
                        fName = "XXXXXXXX";
                        lName = "XXXXXXXX";
                        emailAddress = "XXXXXXXX";
                        phoneNumber = "XXXXXXXX";
                        idNumber = "XXXXXXXX";
                        accountNumber = "XXXXXXXX";

                        if (tempFile.is_open()){
                            tempFile << endl;
                            tempFile << fName << "    " << lName << "    " << emailAddress << "    " << phoneNumber << "    " << idNumber << "    " << pin << "    " << accountNumber << endl; 
                        } else {
                            cout << "could not open file" << endl;
                        }
                    } else {
                        tempFile << endl;
                        tempFile << fName << "    " << lName << "    " << emailAddress << "    " << phoneNumber << "    " << idNumber << "    " << pin << "    " << accountNumber << endl; 
                    }
                }
            } else {
                cout << "could not open file" << endl;
            }
            removeAccount.close();
            tempFile.close();

            // reflect pin change in the main database
            // remove Cached file
            if (remove("CustomerRegistrationFile.bms") != 0){
                cout << "Error removing account" << endl;
            } else {
                cout << "Removing account ... " << endl;
            }

            std::ofstream finalAccountRemoval;
            std::ifstream permFile("temp.bms");
            finalAccountRemoval.open("CustomerRegistrationFile.bms", ios::app);
            if (permFile.is_open()){
                int count = 0;
                while (count < (countRecords("temp.bms")-1)){
                    getline(permFile, tempRecord);
                    finalAccountRemoval << endl;
                    finalAccountRemoval << tempRecord;
                    ++ count;
                }
                cout << "Account Removed successfully!" << endl;
            } else {
                cout << "could not open file" << endl;
            }

            finalAccountRemoval.close();
            permFile.close();
            if (remove("temp.bms") != 0){
                system(CLEAR);
                cout << "Error removing account" << endl;
            } else {
                system(CLEAR);
                cout << transactionCode << ". Your balance was ksh." << totalBalance -(cost(totalBalance)) << endl;
            }
            logout();
        } else if (option == 'n'){
            system(CLEAR);
            account();
        } else {
            cout << "invalid choice!" << endl;
        }
    }
}


// Check if customer selects an acceptable character
int validIntegerInput(int begin, int end){
    int input;
    int length = 0;
    cin >> input;
    while (cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cout << "Bad entry. [" << begin << " - " << end << "] >";
        cin >> input;
    }

    return input;
}

