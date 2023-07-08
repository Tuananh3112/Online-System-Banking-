#ifndef LOGIN_H
#define LOGIN_H
#include<bits/stdc++.h>
using namespace std;

class Login
{
private:
	char phonenum[50];
	char ac[50];
	char password[50];
	char filename[50];
	double balance;
public:
	Login t(char phonenum, char ac, char password, double balance,char filename)
	{
		*this->phonenum = phonenum;
		*this->password = password;
		*this->ac = ac;
		 this->balance = balance;
		*this->filename = filename;
	}
	virtual void savefileregister();
	virtual void login();
	void transfer(Login recipient);

};



#endif