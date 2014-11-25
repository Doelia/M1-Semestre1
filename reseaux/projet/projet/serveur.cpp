#include "commun/header-commun.h"
#include "serveur/includes-serveur.h"

int main() {

	ThreadManager::init();

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock != -1) {

		struct sockaddr_in addr;
		addr.sin_addr.s_addr    = htonl(INADDR_ANY);
		addr.sin_family			= AF_INET;
	 	addr.sin_port			= htons(PORT_SERVER);
	 	
		int retourBind = bind(sock, (sockaddr*)&addr, sizeof(addr));
		
		if (retourBind != -1) {
			Interface::log("Bind OK");

			int retourListen = listen(sock, 5);
			if (retourListen != -1) {
				Interface::log("listen() sur le port %d OK", PORT_SERVER);

				sockaddr_in addrClient;
				socklen_t size = sizeof(addrClient);
				int sockClient;

				Interface::log("En attente de connexion...");
				while (sockClient = accept(sock, (sockaddr*)&addrClient, &size)) {

					Interface::log("Un client se connecte avec la socket %d de %s:%d", sockClient, inet_ntoa(addrClient.sin_addr), htons(addrClient.sin_port));
					ClientConnexion* cc = new ClientConnexion(sockClient);
					pthread_t* id = (pthread_t*) malloc(sizeof(int));
					pthread_create(id, NULL, client_listeMessages, (void *) cc);
					ThreadManager::getInstance()->add((int) *id);
					Interface::log("En attente de connexion...");
				}
			}
			else {
				Interface::log("Impossible d'écouter sur le port %d", PORT_SERVER);
			}
		}
		else {
			Interface::log("Bind de la socket sur le port %d impossible", PORT_SERVER);
		}

	}
	else {
		Interface::log("Erreur creation de socket");
	}

	Interface::log("Lancement du serveur...");

	ThreadManager::getInstance()->joinAll();
}

