#ifndef THREADMANAGER
#define THREADMANAGER

#include "header-commun.h"

class ThreadManager {
	public:
		static ThreadManager* getInstance();
		static void init();
		ThreadManager();
		void joinAll();
		void display(string s);
		void add(int t);
	private:
		static ThreadManager* instance;
		vector<int>* threads;
};

#endif