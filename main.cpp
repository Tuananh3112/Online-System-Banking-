#include"ACCOUNT.h"
#include"BANK.h"
#include"LOGIN.h"

int main()
{
    
    
    Login dsLogin;
    int choice;
    
    
    do
    {
        
        cout << "---- Welcome to Bank Online System ----" << endl;
        cout << "\nPlease login or register to access the Banking Online !";
        cout << "\n1. Create a new account";
        cout << "\n2. Login to an account";
        cout << "\n3. Exit";
        
        cout << "\n\nPress your choice:\t";
        cin >> choice;
        
        switch (choice)
        {
        case 1:
        {
            system("cls");
            dsLogin.savefileregister();
            break;
        }

        case 2:
        {
            system("cls");
            dsLogin.login();
            break;
        }
        case 3:
        {
            cout << "Thank you for using the Online Banking System.\n";
            break;
        }
        }

    } while (choice != 3);
	return 0;
}

