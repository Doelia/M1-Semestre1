#include "Shell.h"

Shell* Shell::instance = NULL;

Shell* Shell::getInstance() {
	return Shell::instance;
}

void Shell::init() {
	Shell::instance = new Shell();
}

void Shell::welcomeMsg() {
	cout << "Bienvenue sur le serveur" << endl;
}

void Shell::printPrompt() {
	cout << "Entrez une commande. Tapez 'help' pour avoir de l'aide" << endl;
	cout << "> ";
}