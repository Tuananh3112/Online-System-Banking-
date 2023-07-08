#include"LOGIN.h"
#include"ACCOUNT.h"

void Login::transfer(Login recipient) {
    double amount;
    char filename[50];
    cout << "\nEnter the amount to transfer: ";
    cin >> amount;

    if (balance >= amount) {
        balance -= amount;
        recipient.balance += amount;
    }
    else {
        cout << "\nInsufficient balance to transfer." << endl;
    }
    strcpy_s(filename, sizeof(filename), phonenum);
    strcat_s(filename, sizeof(filename), ".txt");

    ofstream f(filename);
    f << "Account: " << ac << endl;
    f << "Phone number: " << phonenum << endl;
    f << "Password: " << password << endl;
    f << "Balance: " << balance << endl;
    f.close();


    ofstream recipientFile(filename);
    recipientFile << "Account: " << recipient.ac << endl;
    recipientFile << "Phone number: " << recipient.phonenum << endl;
    recipientFile << "Password: " << recipient.password << endl;
    recipientFile << "Balance: " << recipient.balance << endl;
    recipientFile.close();
}


void Login::savefileregister() {
    ostringstream oss;
    char filename[50];

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter your phone number: ";
    cin.getline(phonenum, sizeof(phonenum));

    cout << "Enter your new account: ";
    cin.getline(ac, sizeof(ac));

    cout << "Enter your password: ";
    cin.getline(password, sizeof(password));

    cout << "Enter the money you want to add: ";
    cin >> balance;

    oss << "Account: " << ac << endl;
    oss << "Phone number: " << phonenum << endl;
    oss << "Password: " << password << endl;
    oss << "Balance: " << balance << endl;

    strcpy_s(filename, sizeof(filename), phonenum);
    strcat_s(filename, sizeof(filename), ".txt");

    ofstream f(filename);

    if (!f) {
        cout << "Failed to open the file." << endl;
    }
    else {
        f << oss.str(); 
        cout << "\n\nAccount successfully registered!" << endl;
    }

    f.close();
}

void Login::login() {
    ifstream f;
    ofstream fp;
    
    bool passwordmatched = false;
    char filename[50];
    double amount;
    cout << "\t\t\t\t\t\tSIGN IN\t\t\t\n";
    cout << "\t\t\t\t\tPlease sign in to proceed.\t\t\t\t\t\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter your phone number: ";
    cin.getline(phonenum, sizeof(phonenum));

    cout << "Enter your password: ";
    cin.getline(password, sizeof(password));

    balance = 0;  

    strcpy_s(filename, sizeof(filename), phonenum);
    strcat_s(filename, sizeof(filename), ".txt");

    f.open(filename);

    if (!f) {
        cout << "Failed to open the file." << endl;
    }


    else {
        char line[100];
       
        while (f.getline(line, sizeof(line))) {
            if (strncmp(line, "Password: ", 10) == 0) {
                char storedPassword[50];
                strcpy_s(storedPassword, sizeof(storedPassword), line + 10);

                if (strncmp(storedPassword, password, sizeof(password)) == 0) {
                    passwordmatched = true;
                }
            }
            else if (strncmp(line, "Balance: ", 9) == 0) {
                balance = atof(line + 9);  
            }
        }
        if (passwordmatched) {
            char choice;
            int option;

            do {
                system("cls");
                cout << "\n 1. Information of your account";
                cout << "\n 2. Depositing cash";
                cout << "\n 3. Cash withdrawal";
                cout << "\n 4. Transfer funds";
                cout << "\n\t\tYour choice: ";
                cin >> option;

                switch (option) {
                case 1:
                    cout << "\nYour balance is " << balance << " $" << endl;
                    break;
                case 2:
                    fp.open(filename);
                    cout << "\nEnter the amount: ";
                    cin >> amount;
                    balance += amount;
                    fp << "Account: " << ac << endl;
                    fp << "Phone number: " << phonenum << endl; 
                    fp << "Password: " << password << endl;
                    fp << "Balance: " << balance << endl;  
                    if (!fp) {
                        cout << "\nFailed to deposit!" << endl;
                    }
                    else {
                        cout << "\nSuccessfully deposited." << endl;
                    }
                    fp.close();
                    break;
                case 3:
                    cout << "\nEnter the amount: ";
                    cin >> amount;
                    if (balance >= amount) {
                        balance -= amount;   
                        cout << "\nSuccessfully deposited." << endl;
                    }
                    else if(balance < amount) {
                        cout << "\nInsufficient balance to withdraw." << endl;
                    }
                    fp.open(filename);
                    fp << "Account: " << ac << endl;
                    fp << "Phone number: " << phonenum << endl;
                    fp << "Password: " << password << endl;
                    fp << "Balance: " << balance << endl;
                    if (!fp) {
                        cout << "\nFailed to withdraw!" << endl;
                    }
                    else {
                        cout << "\nFinish the transfer" << endl;
                    }
                    fp.close();
                    break;
                case 4: {
                    Login recipient;
                    cin.ignore();
                    cout << "\nEnter the recipient's phone number: ";
                    cin.getline(recipient.phonenum, sizeof(recipient.phonenum));

                    char recipientFilename[50];
                    strcpy_s(recipientFilename, sizeof(recipientFilename), recipient.phonenum);
                    strcat_s(recipientFilename, sizeof(recipientFilename), ".txt");

                    ifstream recipientFile(recipientFilename);

                    if (!recipientFile) {
                        cout << "Recipient's account not found!" << endl;
                    }
                    else if (strcmp(recipient.phonenum, phonenum) == 0) {
                        cout << "Cannot transfer funds to your own account!" << endl;
                    }
                    else {
                        recipientFile.close();
                        transfer(recipient); // Perform the transfer from recipient to the current user
                    }
                    break;
                
                }
                default:
                    cout << "Invalid option!" << endl;
                    break;
                }

                cout << "\nDo you want to continue? (y/n) ";
                cin >> choice;

                if (choice != 'y') {
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } while (true);
        }
        else {
            cout << "\nInvalid Password!" << endl;
        }
    }

    if (!passwordmatched) {
        cout << "Account number not registered!" << endl;
    }

    f.close();
}

