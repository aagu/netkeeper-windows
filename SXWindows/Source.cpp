#include "SXEncryption.h"
#include "VpnUtils.h"
#include "HashUtils.h"
#include <iostream>
#include <fstream>

string Operator;
string username;
string password;
string server;
int choice;

#define fname "sx.txt"
#define LNS_T "220.191.128.9"
#define LNS_M "192.168.193.10"

void init() {
	ifstream fin(fname);
	if (fin.good()) {
		fin >> Operator >> username >> password >> server;
		cout << "read config success, operator£º" << Operator << "username: " << username <<  "server: " << server << endl;
	}
	else {
		cout << "could not find config file." << endl;
		cout << "please choose youe operator:\n1.China Telecomm  2.China Mobile" << endl;
		cin >> choice;
		if (choice == 1) {
			server = LNS_T;
			cout << "please input your sx username, with @LGDX.XY :" << endl;
			cin >> username;
			cout << "please input your password :" << endl;
			cin >> password;
		}
		else if (choice == 2) {
			server = LNS_M;
			cout << "please input your username  :" << endl;
			cin >> username;
			cout << "please input your password :" << endl;
			cin >> password;
		}
		else
			cout << "Invalid choice!" << endl;
		ofstream fout(fname);
		fout << Operator << username << endl << password << endl << server << endl;
	}
}

int main() {
	init();
	cout << "dialing, please wait." << endl;
	if (choice == 1) {
		try {
			SXEncryption sx(username, password, server);
			sx.raiseVpn(1);
		}
		catch (exception &ex) {
			cout << ex.what() << endl;
			system("pause");
			return -1;
		}
	}
	else {
		try {
			SXEncryption sx(username, password, server);
			sx.raiseVpn(0);
		}
		catch (exception &ex) {
			cout << ex.what() << endl;
			system("pause");
			return -1;
		}
	}
	cout << "vpn dial up success." << endl;
	Sleep(2000);
	return 0;
}