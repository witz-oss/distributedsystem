#ifndef DISTRIBUTEDSYSTEM_DATABASE_H
#define DISTRIBUTEDSYSTEM_DATABASE_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include <map>
#include "Http.h"

#define PORTDB 9080
#define BUFSIZE 16384

class Database{
private:
    std::map<std::string, std::string> dataBaseMap;
    int dbSockDest, cliSock;
    struct sockaddr_in dbAddress, cliAddress;
    struct timeval tv{};
    char buffer[BUFSIZE]{};
public:
    Database(){};
    ~Database() {
        close(dbSockDest);
    }
    void init(){
        /*** Socket Creation ***/
        if ((dbSockDest = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        dbAddress.sin_family = AF_INET;
        dbAddress.sin_addr.s_addr = INADDR_ANY;
        dbAddress.sin_port = htons(PORTDB);

        /*** Forcefully attaching socket to the port 8080 ***/
        if (bind(dbSockDest, (struct sockaddr*)&dbAddress, sizeof(dbAddress)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(dbSockDest, 100) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }
    void listening(){

        gettimeofday(&tv, nullptr);
        double t1 = 1.0e6 * (double) tv.tv_sec + tv.tv_usec;

        if ((cliSock = accept(dbSockDest, (struct sockaddr*)&cliAddress, (socklen_t*)&cliAddress)) < 0) {
            perror("\nConnection Failed\n");
            exit(EXIT_FAILURE);
        }

        read(cliSock, buffer, BUFSIZE);
        std::string str = buffer;
        memset(buffer, 0, sizeof(buffer));
        Http http = Http(str);
        std::string request = http.getRequest();


        if(request == "GET"){
            std::string msg;
            if(http.getIdRequest() == "/") {
                for (const auto &item: dataBaseMap)
                    msg += item.second;
                std::string msgSend = http.creatOK(msg);
                send(cliSock, msgSend.c_str(), msgSend.length(), 0);
            } else {
                msg = http.Creat404();
                send(cliSock, msg.c_str(), msg.length(), 0);
            }
        }else if(request == "POST"){
            std::vector<std::string> vecTemp = http.msgPOST();
            dataBaseMap[vecTemp.at(0)] = vecTemp.at(1);
        }
        close(cliSock);

        gettimeofday(&tv, nullptr);
        double t2 = 1.0e6 * (double) tv.tv_sec + tv.tv_usec;
        std::cout << "\nRound-Trip-Time(" << request<< "): " << (t2 - t1) << std::endl;
    }
};



#endif //DISTRIBUTEDSYSTEM_DATABASE_H
