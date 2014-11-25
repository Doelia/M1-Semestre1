//
//  client.cpp
//  test_transfert
//
//  Created by Stéphane on 25/11/2014.
//  Copyright (c) 2014 Stéphane. All rights reserved.
//

#include "commun.h"
#include "client.h"

int sock;

void* ecrire(void* x) {
    while (true) {
        char buffer[32] = {'\0'};
        cin >> buffer;
        if(write(sock, buffer, (ssize_t) 32) == -1)
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

        }
        else {
            cout << "Erreur à la connexion\n";
        }
    }
    else {
        cout << "Erreur creation de socket\n";
    }
    
}
