#include "SXEncryption.h"
#include "VpnUtils.h"
#include "HashUtils.h"
#include <iostream>
#include <fstream>

string username;
string password;
string server;

#define fname "sx.txt"

void init() {
	ifstream fin(fname);
	if (fin.good()) {
		fin >> username >> password >> server;
		cout << "read config success, username: " << username << " server: " << server << endl;
	}
	else {
		cout << "could not find config file." << endl;
		cout << "please input your sx username, with @LGDX.XY :" << endl;
		cin >> username;
		cout << "please input your password :" << endl;
		cin >> password;
		cout << "please input vpn server, if you don't know, please contact the author :" << endl;
		cin >> server;
		ofstream fout(fname);
		fout << username << endl << password << endl << server << endl;
	}
}

int main() {
	init();
	cout << "dialing, please wait." << endl;
	try {
		SXEncryption sx(username, password, server);
		sx.raiseVpn();
	}
	catch (exception &ex) {
		cout << ex.what() << endl;
		system("pause");
		return -1;
	}
	cout << "vpn dial up success." << endl;
	return 0;
}