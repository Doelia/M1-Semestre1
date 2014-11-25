#include "header-serveur.h"

void Interface::log(string s) {
	cout << "[server] " << s << endl;
}

void Interface::log(string s, int v) {
	char out[2048];
	sprintf(out, s.c_str(), v);
	cout << "[server] " << out << endl;
}

void Interface::log(string s, int v, string s1, int v2) {
	char out[2048];
	sprintf(out, s.c_str(), v, s1.c_str(), v2);
	cout << "[server] " << out << endl;
}

