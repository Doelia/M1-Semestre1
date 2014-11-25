#include "commun/header-commun.h"
#include "client/header-client.h"

int main() {

    ThreadManager::init();
    Shell::init();
    NetworkManager* networkManager = NetworkManager::init();

	cout << "Lancement du client..." << endl;
    
    if (networkManager->connectToServer("127.0.0.1", PORT_SERVER)) {
        networkManager->start_listenMessages();
        networkManager->sendPaquet("coucou 1");
        networkManager->sendPaquet("coucou 2");
        sleep(1);
    }

    ThreadManager::getInstance()->joinAll();
    
}

