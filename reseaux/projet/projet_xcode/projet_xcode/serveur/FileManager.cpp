
#include "FileManager.h"

FileManager* FileManager::instance = NULL;

FileManager* FileManager::getInstance() {
	return FileManager::instance;
}

FileManager* FileManager::init() {
	FileManager::instance = new FileManager();
	return FileManager::instance;
}

bool FileManager::exists(string nameFile) {
	return false;
}


