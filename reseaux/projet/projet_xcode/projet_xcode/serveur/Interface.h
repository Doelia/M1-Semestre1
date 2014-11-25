#ifndef INTERFACE_H
#define INTERFACE_H

#include "header-serveur.h"

class Interface {
public:
	static void display(string, int);
	static void log(string);
	static void log(string, int);
	static void log(string, int, string, int);
};

#endif

