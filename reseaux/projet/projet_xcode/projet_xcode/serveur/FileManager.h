#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "header-serveur.h"

class FileManager {

public:
	static FileManager* getInstance();
	static FileManager* init();

	bool exists(string);
private:
	static FileManager* instance;

};

#endif
