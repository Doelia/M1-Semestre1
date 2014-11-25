#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

using namespace std;

int sock;

void* ecrire(void* x) {
	while (true) {
		char buffer[32] = {'\0'};
		cin >> buffer;
		int sock_err = write(sock, buffer, 32);
	    if(sock_err == -1)
	       cout << "Erreur de transmission\n";
	}
}

void* lire(void* x) {
	while (true) {
		char buf[32] = {0};
		recv(sock, buf, 32, 0);
		cout << "Reçu: " << buf << "\n";
   	}
}

int main() {

	pthread_t p_write;
	pthread_t p_read;

	int port = 25573;
	string ip = "127.0.0.1";

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock != -1) {

		struct sockaddr_in addr;
		addr.sin_addr.s_addr    = inet_addr(ip.c_str());
		addr.sin_family         = AF_INET;
	 	addr.sin_port           = htons(port);

		if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != -1) {
			cout << "Conexion au seveur OK\n";
			int x = 3;
			pthread_create(&p_write, NULL, ecrire, &x);
			pthread_create(&p_read, NULL, lire, &x);
		}
		else {
			cout << "Erreur à la connexion\n";
		}
	}
	else {
		cout << "Erreur creation de socket\n";
	}

	pthread_join(p_write, NULL);
	pthread_join(p_read, NULL);
}

