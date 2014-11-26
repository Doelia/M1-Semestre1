#include "NetworkManager.h"

NetworkManager* NetworkManager::instance = NULL;

NetworkManager* NetworkManager::getInstance() {
	return NetworkManager::instance;
}

NetworkManager* NetworkManager::init() {
	NetworkManager::instance = new NetworkManager();
	return NetworkManager::instance;
}

bool NetworkManager::connectToServer(string ip, int port) {
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock != -1) {
        
        struct sockaddr_in addr;
        addr.sin_addr.s_addr    = inet_addr(ip.c_str());
        addr.sin_family         = AF_INET;
        addr.sin_port           = htons(port);
        
        cout << "Connexion à " << ip << ":" << port << "..." << endl;
        if (::connect(sock, (sockaddr*)&addr, sizeof(addr)) != -1) {
            cout << "Connecté au seveur !\n";
            return true;
        }
        else {
            cout << "Impossible de se connecter au serveur.\n";
        }
    }
    else {
        cout << "Erreur creation de socket\n";
    }

    return false;
}

void* networkManager_listenMessages(void *c) {
	NetworkManager::getInstance()->listenMessages();
	return NULL;
}

void NetworkManager::start_listenMessages() {
	pthread_t* id = (pthread_t*) malloc(sizeof(int)*2);
	pthread_create(id, NULL, networkManager_listenMessages, NULL);
	ThreadManager::getInstance()->add(id);
}


void NetworkManager::listenMessages() {
	
}

void NetworkManager::onPaquet(string paquet) {
	vector<string> parts = split(paquet, ':');
	if (parts.at(0) == "MSG") {
		this->onPaquet_message(parts.at(1));
	}
}

void NetworkManager::onPaquet_message(string message) {
	cout << "Message reçu du serveur : " << message << endl;
}

bool NetworkManager::sendPaquet(string paquet) {
	cout << "Tentative d'envoi du paquet " << paquet << endl;
	char* buffer;
	initBuffer(&buffer, 32);

	if (paquet.size() >= MAX_SIZE_PAQUETS) {
		cout << "Paquet trop gros" << endl;
		return false;
	}

	for (int i=0; i < paquet.size(); i++) {
		buffer[i] = paquet.at(i);
	}

	int sock_err = send(this->sock, buffer, MAX_SIZE_PAQUETS, 0);
	return true;
}
