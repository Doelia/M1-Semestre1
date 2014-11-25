#include "ClientConnexion.h"

ClientConnexion::ClientConnexion(int socket) {
	this->sock = socket;
}

void* client_listeMessages(void* c) {
	ClientConnexion* cc = (ClientConnexion*) c;
	cc->listenMessages();
}

void ClientConnexion::listenMessages() {
	char buf[MAX_SIZE_PAQUETS] = {0};

	Interface::log("En attente de messages...");
	while (int retour = recv(this->sock, buf, MAX_SIZE_PAQUETS, 0)) {
		Interface::log("En attente de messages...");
	}
}
