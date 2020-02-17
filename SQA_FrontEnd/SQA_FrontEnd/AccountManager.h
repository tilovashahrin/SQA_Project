#pragma once
#include "UserActivity.h"
#include <string>
#include <iostream>
using namespace std;

class AccountManager : public UserActivity
{
private:
	bool logStatus; // true = logged in, false = logged out
	char user_type; // AA=admin, FS=full-standard, BS=buy-standard,SS=sell-standard
	string username;

public:
	AccountManager();

	AccountManager(bool _logStatus, char _user_type, string _username ); // For Testing Purposes

	int login(string _username); // 0 = Success, 1 = Already Logged In, 2 = No Account

	int logout(); // 0 = Success, 1 = Already Logged Out

	int createUser();

	void deleteUser() {};

	bool verifyLogin() {};

	string getUsername() { return username; };
	bool getLogStatus() { return logStatus; };
	char getUserType() { return user_type; };
};

