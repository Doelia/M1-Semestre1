#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "header-client.h"

void* networkManager_listenMessages(void *c);

class NetworkManager {

public:
	static NetworkManager* getInstance();
	static NetworkManager* init();

	bool connectToServer(string, int);
	bool sendPaquet(string);
	void start_listenMessages();
	void listenMessages();

private:
	static NetworkManager* instance;

	void onPaquet(string);
	void onPaquet_message(string);

	int sock;

};

#endif
