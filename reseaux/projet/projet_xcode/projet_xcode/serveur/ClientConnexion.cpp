#include "ClientConnexion.h"

ClientConnexion::ClientConnexion(int socket) {
	this->sock = socket;
}

void* client_listeMessages(void* c) {
	ClientConnexion* cc = (ClientConnexion*) c;
	cc->listenMessages();
    return NULL;
}

void ClientConnexion::start_listenMessages() {
	pthread_t* id = (pthread_t*) malloc(sizeof(int)*2);
	pthread_create(id, NULL, client_listeMessages, (void *) this);
	ThreadManager::getInstance()->add(id);
}


void ClientConnexion::listenMessages() {
	char* buff;
	initBuffer(&buff, 32);
	int retour;
	while ((retour = recv(this->sock, buff, MAX_SIZE_PAQUETS, 0)) > 0) {
		this->sendPaquet(buff);
		initBuffer(&buff, 32);
	}
    cout << "Fin d'attende de message." << endl;
}

int ClientConnexion::sendPaquet(string paquet) {
	cout << "Tentative d'envoi du paquet '" << paquet << "' au serveur" << endl;

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
