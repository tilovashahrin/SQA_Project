#include "UserActivity.h"
#include <string>
#include <iostream>
#include <limits>
using namespace std;

UserActivity::UserActivity() {
	itemFile = "DataFiles/ItemDB.txt";
	item_name =""; //less than 25 characters
	num_days = 1; //less than 100 days
	min_bid = 00.00; //less than 999.99
	bid_amount = 00.00;
	transf_credit = 00.00;
	refund_credit = 00.00;
	previous_bid = 00.00;
	sellers_username = "";
	buyers_username = "";
	credit_username = "";
}

UserActivity::UserActivity(string file) {
	itemFile = file;
	item_name =""; //less than 25 characters
	num_days = 1; //less than 100 days
	min_bid = 00.00; //less than 999.99
	bid_amount = 00.00;
	transf_credit = 00.00;
	refund_credit = 00.00;
	previous_bid = 00.00;
	sellers_username = "";
	buyers_username = "";
	credit_username = "";
}

//have user create a bidding advertisement
void UserActivity::advertise(string sellers_username) {
	cout << "\nEnter the name of the item (in 25 characters or less): ";
	cin.ignore(100,'\n');
	getline(cin, item_name,'\n');
	if (item_name.length() >= 25) {
		cout << "\nERROR! item name exceeded limit. Please try again.";
		exit(1);//return;
	}

	cout << "\nEnter minimum bid (eg 15.00): ";
	if (!(cin >> min_bid)) {
		cin.clear(); //clear bad input flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
		cout << "\nERROR: Inavlid input. Please try again.\n";
		exit(1);//return;//return;
	}
	if (min_bid > 999.99) {
		cin.clear(); //clear bad input flag
		cout << "\nERROR: Maximum price exceeded for minimum bid. Minimum bid must be $999.99 or less.\n";
		exit(1);//return;
	}

	cout << "\nEnter number of days available to bid: ";
	
	if (!(cin >> num_days)) {
		cin.clear(); //clear bad input flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
		cout << "\nERROR: Inavlid input. Please try again.\n";
		exit(1);//return;//return;
	}
	if (num_days > 100) {
		cin.clear(); //clear bad input flag
		cout << "\nERROR: Max number of days exceeded.\n";
		exit(1);//return;
	}
	
	cout << "\nAdvertisement Complete. Information saved into the daily transaction file.\n";
	Transaction::adv_trans(item_name, sellers_username, num_days, min_bid);
	
}

void UserActivity::bid(string user_type) {
	float previous_bid = getPreviousBid();

	cout << "== Create a bid ==";
	cout << "\n Enter the item name: ";
	cin.ignore(100, '\n');
	getline(cin, item_name, '\n');

	cout << "\nEnter seller's username: ";
	cin >> sellers_username;
		
	if (user_type != "AA") {
		cout << "\nOur last bidding is at " << previous_bid << ".\n You must bid at least 5% higher than the previous bid shown above.\nEnter here (eg. 230.00): ";
		if (!(cin >> bid_amount)) {
			cin.clear(); //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			cout << "\nERROR: Inavlid input. Please try again.\n";
			exit(1);//return;
		}
		if (bid_amount < ((0.05 * previous_bid) + previous_bid)) {
			cout << "\nERROR: bid is less than the minimum amount.";
			exit(1);//return;
		}
		bid_amount = previous_bid;
	}
	else {
		cout << "\nEnter your bid amount here: ";
		if (!(cin >> bid_amount)) {
			cin.clear(); //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			cout << "ERROR: Inavlid input. Please try again.\n";
			exit(1);//return;
		}
		bid_amount = previous_bid;
	}
	cout << "\nBid Complete. Information saved into the daily transaction file.\n";
	Transaction::bid_trans(item_name, sellers_username, buyers_username, bid_amount);
}

void UserActivity::addCredit(string user_type) {
	cout << "\nIn a given session, you must enter a credit amount of less than $1000\n";
	if (user_type != "AA") {
		cout << "\nEnter amount: ";
		if (!(cin >> transf_credit)) {
			cin.clear(); //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			cout << "\nERROR: Inavlid input. Please try again.\n";
			exit(1);//return;
		}
		if (transf_credit > 1000) {
			cout << "ERROR! Exceeded transfer limit. Please try again.";
			exit(1);//return;
		}
	}
	else {
		cout << "\nEnter username to which credit is being added: ";
		cin >> credit_username;
		cout << "\nEnter amount: ";
		if (!(cin >> transf_credit)) {
			cin.clear(); //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			cout << "\nERROR: Inavlid input. Please try again.\n";
			exit(1);//return;
		}
		if (transf_credit > 1000) {
			cout << "ERROR! Exceeded transfer limit. Please try again.";
			exit(1);//return;
		}
		if (verifyLogin(credit_username) == true) {
			cout << "ERROR: This user does not exist.\n";
			exit(1);//return;
		}
	}
	cout << "\nCredit transaction complete. Information saved into the daily transaction file.\n";
	Transaction::logout_trans(06, buyers_username, user_type, transf_credit);
}

void UserActivity::refund(string user_type) {
	if (user_type == "AA") {
		cout << "\nEnter buyer's username: ";
		cin >> buyers_username;

		cout << "\nEnter seller's username: ";
		cin >> sellers_username;

		cout << "\nEnter the amount of credit you wish to transfer: ";
		if (!(cin >> refund_credit)) {
			cin.clear(); //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			cout << "\nERROR: Inavlid input. Please try again.\n";
			exit(1);//return;
		}
	}
	else {
		cout << "\n ERROR! You do not have authorization to value refunds.\n";
		exit(1);
	}
	cout << "\nRefund Complete. Information saved into the daily transaction file.\n";
	Transaction::refund_trans(buyers_username, sellers_username, refund_credit);
}

