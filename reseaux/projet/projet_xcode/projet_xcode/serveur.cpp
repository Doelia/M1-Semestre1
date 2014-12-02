#include "commun/header-commun.h"
#include "serveur/header-serveur.h"

int main() {

	ThreadManager::init();

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock != -1) {

		struct sockaddr_in addr;
		addr.sin_addr.s_addr    = htonl(INADDR_ANY);
		addr.sin_family			= AF_INET;
	 	addr.sin_port			= htons(PORT_SERVER);
	 	
        int retourBind = ::bind(sock, (sockaddr*)&addr, sizeof(addr));
		
		if (retourBind != -1) {
			cout << "Bind OK" << endl;

			int retourListen = listen(sock, 5);
			if (retourListen != -1) {
				cout << "listen() sur le port " << PORT_SERVER << " OK" << endl;
 
				sockaddr_in addrClient;
				socklen_t size = sizeof(addrClient);
				int sockClient;

				cout << "En attente de connexion..." << endl;
				while ((sockClient = accept(sock, (sockaddr*)&addrClient, &size))) {

					cout << "Un client se connecte avec la socket " << sockClient << " de " << inet_ntoa(addrClient.sin_addr) << ": " << htons(addrClient.sin_port) << endl;
					ClientConnexion* cc = new ClientConnexion(sockClient);
					cc->start_listenMessages();
					cout << "En attente de connexion..." << endl;
				}
			}
			else {
				cout << "Impossible d'écouter sur le port " << PORT_SERVER << endl;
			}
		}
		else {
			cout << "Bind de la socket sur le port " << PORT_SERVER << " impossible" << endl;
		}

	}
	else {
		cout << "Erreur creation de socket" << endl;
	}


	ThreadManager::getInstance()->joinAll();
}

