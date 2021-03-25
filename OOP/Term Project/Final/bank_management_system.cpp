#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

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

class CheckInput{
    public:
        // Check if customer selects an acceptable character
        int validIntegerInput(int begin, int end){
            int input;
            int length = 0;
            cin >> input;
            while (cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Bad entry. [" << begin << " - " << end << "] >";
                cin >> input;
            }

            return input;
        }

};


class Customer: public CheckInput{
    public:
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
            random_device random_num_generator;
            uniform_int_distribution<int> int_distribution(48,57);
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
            random_device random_num_generator;
            uniform_int_distribution<int> int_distribution(65,90);
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
            cout << "---------------------------------------------------\n";
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
            vector<string> fileRecord;
            string record;
            string value = flag("CustomerRegistrationConfigurationFile.txt"); // check the value stored in configuration file
                
            if (value != "true"){
                ofstream customerRegistration("CustomerRegistrationFile.bms", ios::app);
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

            ofstream customerRegistration("CustomerRegistrationFile.bms", ios::app);
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
            ifstream fileCheck("CustomerRegistrationFile.bms");
            ofstream session;
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
            ifstream configurationFile(fileName);
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
            ifstream recordSearch("CustomerRegistrationFile.bms");
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
            vector<string> fileRecord;
            string record;
            string value = flag("accountConfigurationFile.txt"); // check the value stored in configuration file
                
            if (value != "true"){
                ofstream customerRegistration("AccountFile.bms", ios::app);
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
            ifstream fileCheck("AccountFile.bms");
            ofstream session;
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
            ofstream accountUpdate("AccountFile.bms", ios::app);
            double amount, serviceFee, newBalance, displayTotal=0;
            string transactionCode = generateTransactionCode();
            cout << "Enter Amount: ";
            cin >> amount;
            serviceFee = cost(amount);
            newBalance = amount - serviceFee;
            displayTotal = total(tempAccountNumber);
            if (displayTotal < 0){
                displayTotal = 0;
            }

            if (accountUpdate.is_open()){
                cout << transactionCode <<". Ksh." << serviceFee << " has been deducted from your account as a service fee. Ksh." << newBalance << " has been sent to your account. Your new balance is Ksh." << displayTotal + newBalance << endl;
                accountUpdate << endl;
                accountUpdate << tempAccountNumber << "    " << newBalance << "    " << transactionCode << "    " << "Deposit    -    0" <<  endl;
                cout << "---------------------------------------------------\n";
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
            ifstream recordSearch("AccountFile.bms");
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
            ofstream accountUpdate("AccountFile.bms", ios::app);
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
                cout << "---------------------------------------------------\n";
                account();
            } else {
                cout << "could not open file" << endl;
            }
            accountUpdate.close();
        }


        //send money
        void sendMoney(){
            ofstream accountUpdate("AccountFile.bms", ios::app);
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
                cout << "---------------------------------------------------\n";
                sendMoney();
            }
            
            while(amount > total(tempAccountNumber)){
                system(CLEAR);
                if ((total(tempAccountNumber)) < 0){
                    cout << "Unsuccessful. You do not have enough cash in your account. Your current balance is Ksh.00.00" << endl;
                    cout << "--------------------------------------------------------------------------------------------\n";
                    account();
                } else {
                    cout << "Unsuccessful. You do not have enough cash in your account. Your current balance is Ksh." << total(tempAccountNumber) << endl;
                }
                
                cout << "--------------------------------------------------------------------------------------------\n";
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
                cout << "---------------------------------------------------\n";
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
            ifstream recordSearch("CustomerRegistrationFile.bms");
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
            cout << "------------------------------------------------------------------------------------------\n";
            account();
        }


        // Get the ministatement of the customer
        void miniStatement(string accountNumber){
            ifstream recordSearch("AccountFile.bms");
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
            ifstream changePin("CustomerRegistrationFile.bms");
            ofstream tempFile;
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

            ofstream finalPinChange;
            ifstream permFile("temp.bms");
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
            cout << "---------------------------------------------------\n";
            account();
        }


        // return the number or records in a file
        int countRecords(string fileName){
            int totalRecords = 0;
            string tempRecord;
            ifstream count(fileName);
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

            ifstream removeAccount("CustomerRegistrationFile.bms");
            ofstream tempFile;
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

                    ofstream finalAccountRemoval;
                    ifstream permFile("temp.bms");
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
                    cout << "---------------------------------------------------\n";
                    account();
                } else {
                    cout << "invalid choice!" << endl;
                }
            }
        }        
}; 


class Employee: public Customer {
    private:
        string employeeId;
        string pin;

    public:
        Employee() {
            employeeId = "admin";
            pin = "123456";
        }


        void registrarMenu(){
            int option;
            system(CLEAR);
            cout <<":: Select an option ::\n[1] Registar employee\n[2] Print employee database\n> ";
            option = validIntegerInput(1, 2);
            switch (option){
                case 1:
                    system(CLEAR);
                    registrarLogin();
                    employeeRegistration();
                    break;
                case 2:
                    system(CLEAR);
                    printEmployeeDatabase();
                    break;
                default:
                system(CLEAR);
                    cout << "invalid option!" << endl;
                    registrarMenu();
            }
        }

        void printEmployeeDatabase(){
            system(CLEAR);
            ifstream openDatabase("employeeRegistrationFile.bms");
            string record;

            if (openDatabase.is_open()){
                while(getline(openDatabase, record)){
                    cout << record << endl;
                }
                openDatabase.close();
            } else {
                cout << "Error! could not open database";
                cout << "/n/n";
                registrarMenu();
            }
        }


        // Create and Open employeeRegistrationFile
        void employeeRegistration(){
            vector<string> fileRecord;
            string record;
            string value = flag("employeeRegistrationConfigurationFile.txt"); // check the value stored in configuration file
                
            if (value != "true"){
                ofstream customerRegistration("employeeRegistrationFile.bms", ios::app);
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
            
            cout << "----------------------------------------------------------\n\n";

            ofstream employeeRegistration("employeeRegistrationFile.bms", ios::app);
            if (employeeRegistration.is_open()){
                employeeRegistration << endl;
                employeeRegistration << fileRecord[0] << "   " << fileRecord[1] << "   " << fileRecord[2] << "   " << fileRecord[3] << "   " << fileRecord[2] << endl;
                system(CLEAR);
                registrarMenu();
            } else {
                cout << "could not open file" << endl;
            }    
        }


        // To apply some logic into knowing when to open/create employeeRegistrationFile
        void employeeRegistrationConfigurationFile(){
            // check if config file exists
            ifstream fileCheck("employeeRegistrationFile.bms");
            ofstream session;
            session.open ("employeeRegistrationConfigurationFile.txt");
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
            employeeRegistration(); // check the value stored in the configuration file
        }


        // checking the value stored in ConfigurationFile
        string flag(string fileName){
            string value;
            ifstream configurationFile(fileName);
            if (configurationFile.is_open()){
                getline(configurationFile, value);
            } else {
                cout << "could not open file" << endl;
            }
            return value;
        }


        // authentication for a employee registrar before account access
        void registrarLogin(){
            system(CLEAR);
            string employeeId, pin;
            int attempts = 0;
            bool flagCredentials;
            while (true){
                cout << ":: press 3 to exit ::" << endl;
                cout << ":: PLEASE FILL THE FOLLOWING FIELDS ::" << endl;
                cout << "Employee Id: ";
                cin >> employeeId;
                if (employeeId =="3")
                    registrarMenu();
                else {
                    cout << "PIN           : ";
                    cin >> pin;

                    if (pin == "3")
                        registrarMenu();
                }

                flagCredentials = pinEmployeeIdSearch(employeeId, pin);

                if (flagCredentials == false){
                    system(CLEAR);
                    cout << "Invalid login credentials" << endl;
                    ++ attempts;
                    if (attempts == ATTEMPTS){
                        system(CLEAR);
                        cout << "Try again later .. " << endl;
                        registrarMenu();
                    }
                } else {
                    system(CLEAR);
                    employeeRegistrationConfigurationFile();
                    break;
                }
            }
        }


        // search for pin and account number in file record
        bool pinEmployeeIdSearch(string field1, string field2){
            bool rightCredentials = false;

            if (field1 == employeeId && field2 == pin)
                rightCredentials = true;
            else
                rightCredentials = false;
            
            return rightCredentials;
        }

        // To apply some logic into knowing when to open/ create AccountFile
        void employeeAccountConfigurationFile(){
            // check if config file exists
            ifstream fileCheck("employeeRegistrationFile.bms");
            ofstream session;
            session.open ("employeeAccountConfigurationFile.txt");
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
        }
};


int main(){

    int option;
    CheckInput optionCheck;

    system(CLEAR);
    while (true){
        cout << "press 0 to exit." << endl;
        cout << ":: Choose a user account ::\n[1] Employee registrar\n[2] Customer\n> ";
        option = optionCheck.validIntegerInput(1, 2);

        if (option == 1){
            Employee registrar;
            registrar.registrarMenu();
        } else if (option == 2){
            Customer customer;
            customer.mainMenu();
        } else {
            cout << "exiting ..." << endl;
            exit(0);
        } 
    }
    
    return 0;
}