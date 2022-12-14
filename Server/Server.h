#ifndef VSPRAKTIKUM_SERVER_H
#define VSPRAKTIKUM_SERVER_H

#include <istream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <thread>
#include <pthread.h>
#include <algorithm>
#include <pthread.h>
#include <map>
#include <sys/time.h>
#include <random>

#include "gen-cpp/RPCTasks.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransport.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

#define BUFSIZE 16384
#define PORT 9080


struct Client{
    int id;
    int port;
    bool isBusy = false;
    bool isDead = false;
    Matrix matrix;
    struct sockaddr_in cliSock{};
};

static int portWorkerRPC = 9090;
static std::vector<Matrix> matrixVec;
static pthread_mutex_t mutex;

class Server {
private:
    int quantityWorkers = atoi(std::getenv("quantityWorkersEnv"));
    int serSockDest{};
    const std::string msgH = "H";
    const std::string msgS = "S";
    struct sockaddr_in serAddr{};
    struct sockaddr_in cliAddr{};
    std::vector<Client> cliAddrVec;

    char buffer[BUFSIZE]{};
    struct timeval timeout;
    struct timeval tv{};
public:
    Server() = default;
    ~Server() {
        close(serSockDest);
    }

    void init(){
        /*** Socket Creation ***/
        if ((serSockDest = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("Server creation error...\n");
            exit(-1);
        }
        /*** Binding to the port ***/
        serAddr.sin_family = AF_INET;
        serAddr.sin_port = htons(PORT);
        serAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(serSockDest, (struct sockaddr*)&serAddr, sizeof(serAddr)) < 0) {
            perror("binding error...\n");
            close(serSockDest);
            exit(-1);
        }
    }
    void initTimeout(){
        timeout.tv_usec = 1;
        if(setsockopt(serSockDest, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0){
            std::cerr << "timeout error...\n";
        }
    }
    int recvMsg(int index){
        memset(buffer, 0, sizeof(buffer));
        socklen_t cliAddrLen = sizeof(cliAddrVec.at(index).cliSock);
        if (recvfrom(serSockDest, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliAddrVec.at(index).cliSock, &cliAddrLen) < 0)
            return 1;
        return 0;
    }
    void sendMsg(int index, const std::string& msg){
        socklen_t cliAddrLen = sizeof(cliAddrVec.at(index).cliSock);
        if (sendto(serSockDest, msg.c_str(), msg.length(), 0, (struct sockaddr *)&cliAddrVec.at(index).cliSock, cliAddrLen) < 0) {
            perror("sending error...\n");
            close(serSockDest);
            exit(-1);
        }
    }

    std::vector<Client> getCliAddrVec(){
        return cliAddrVec;
    }
    void setIDClients(){
        for(int i = 0; i < quantityWorkers; ++i){
            std::cout << "Send ID: " << i << std::endl;
            Client client;
            client.id = i;
            client.port = portWorkerRPC;
            client.cliSock = cliAddr;
            cliAddrVec.push_back(client);
            recvMsg(i);
            std::string msg = std::to_string(i) + "/" + std::to_string(portWorkerRPC);
            sendMsg(i, msg);
            portWorkerRPC++;
        }
    }
    void healthCheck(){
        try {
            gettimeofday(&tv, nullptr);
            double t1 = 1.0e6 * (double) tv.tv_sec + tv.tv_usec;

            for (int i = 0; i < cliAddrVec.size(); ++i) {
                sendMsg(i, msgH);
                if(recvMsg(i)){
                    std::cout << cliAddrVec.at(i).id << " kick out" << std::endl;
                    sendMsg(i, msgS);
                    cliAddrVec.at(i).isDead = true;
                    if(cliAddrVec.at(i).matrix.id != -1)
                        matrixVec.push_back(cliAddrVec.at(i).matrix);
                } else {
                    printf("%s\n", buffer);
                }
            }

            gettimeofday(&tv, nullptr);
            double t2 = 1.0e6 * (double) tv.tv_sec + tv.tv_usec;
            std::cout << "\nRound-Trip-Time(" << cliAddrVec.size() << "): " << (t2 - t1) / (double)cliAddrVec.size() << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what();
        }
    }
};

#endif //VSPRAKTIKUM_SERVER_H