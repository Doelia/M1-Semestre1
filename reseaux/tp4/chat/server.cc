#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

int clients[20];
int nbrClients = 0;

void sendToAllClients(char* message, int size) {
	for (int i=0; i < nbrClients; i++) {
		write(clients[i], message, size);
	}
}

void* gerer_client(void* params) {
	int* sockClient = (int*) params;

	clients[nbrClients++] = *sockClient;

	cout << "Attente d'un message...\n";
	char buf[32] = {0};

	while (read(*sockClient, buf, 32)) {
		cout << "Reçu: " << buf << "\n";

		sendToAllClients(buf, 32);

		/*
		int sock_err = send(sockClient, "retour", 32, 0);
        if(sock_err != -1)
            cout << "Message envoyé !\n";
        else
           cout << "Erreur de transmission\n";
		*/

   }
   	cout << "Erreur lors du recv\n";
}

int main() {

	int port = 25573;

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock != -1) {

		sockaddr_in addr;
		addr.sin_addr.s_addr    = htonl(INADDR_ANY);
		addr.sin_family         = AF_INET;
	 	addr.sin_port           = htons(port);
	 	
		int retourBind = bind(sock, (sockaddr*)&addr, sizeof(addr));
		
		if (retourBind != -1) {
			cout << "Bind OK\n";

			int retourListen = listen(sock, 5);
			if (retourListen != -1) {
				cout << "listen() sur le port " << port << " OK\n";

				sockaddr_in addrClient;
				socklen_t size;
				int sockClient;

				cout << "En attente de connexion...\n";
				while (sockClient = accept(sock, (sockaddr*) &addrClient, &size)) {
					
					cout << "Un client se connecte avec la socket "<< sockClient << " de " << inet_ntoa(addrClient.sin_addr) << ":"<<htons(addrClient.sin_port)<<"\n";

					pthread_t id;
					pthread_create(&id, NULL, gerer_client, &sockClient);

					cout << "En attente de connexion...\n";
				}
			}
			else {
				cout << "Impossible d'écouter sur le port " << port << "\n";
			}
		}
		else {
			cout << "Bind de la socket sur le port " << port << " impossible\n";
		}

	}
	else {
		cout << "Erreur creation de socket\n";
	}
}



