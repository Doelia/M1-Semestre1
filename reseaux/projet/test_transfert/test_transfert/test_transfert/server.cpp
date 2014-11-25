//
//  server.c
//  test_transfert
//
//  Created by Stéphane on 25/11/2014.
//  Copyright (c) 2014 Stéphane. All rights reserved.
//

#include "commun.h"
#include "server.h"

int main() {
    int port = 25573;
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock != -1) {
        
        sockaddr_in addr;
        addr.sin_addr.s_addr    = htonl(INADDR_ANY);
        addr.sin_family         = AF_INET;
        addr.sin_port           = htons(port);
        
        int retourBind = ::bind(sock, (sockaddr*)&addr, sizeof(addr));
        
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
                    
                    //pthread_t id;
                   // pthread_create(&id, NULL, gerer_client, &sockClient);
                    
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

