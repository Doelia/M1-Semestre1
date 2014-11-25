#include "ThreadManager.h"

ThreadManager* ThreadManager::instance = NULL;

ThreadManager* ThreadManager::getInstance() {
	return ThreadManager::instance;
}

void ThreadManager::init() {
	ThreadManager::instance = new ThreadManager();
}

ThreadManager::ThreadManager() {
	this->threads = new vector<int>();
}

void ThreadManager::add(int t) {
	this->display("Un thread a été ajouté");
	this->threads->push_back(t);
}

void ThreadManager::display(string s) {
	cout << s << endl;
}

void ThreadManager::joinAll() {
	int n = 0;

	while (n != this->thread.size()) {
		
	}

	for (vector<int>::iterator it=this->threads->begin(); it != this->threads->end(); it++) {
		pthread_join(*it, NULL);
	}
}

