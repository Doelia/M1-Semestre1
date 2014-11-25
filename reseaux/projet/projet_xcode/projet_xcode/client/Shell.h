#ifndef SHELL_H
#define SHELL_H

#include "header-client.h"

class Shell {

public:
	static Shell* getInstance();
	static void init();

	void welcomeMsg();
	void printPrompt();

private:
	static Shell* instance;

};

#endif
