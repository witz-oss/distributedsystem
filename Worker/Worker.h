#ifndef VSPRAKTIKUM_WORKER_H
#define VSPRAKTIKUM_WORKER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/time.h>
#include <pthread.h>
#include <map>
#include <time.h>
#include "Http.h"

#include <iostream>
#include "gen-cpp/RPCTasks.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace apache::thrift::concurrency;

#define PORTDB 9080
#define PORT 9080
#define BUFSIZE 16384

class Worker {
private:
    std::string id;
    int portRTC;
    std::string messageToDB;
    bool kickOut = true;
    int cliSockDestUDP, cliSockDestTCP;
    struct sockaddr_in serAddrUDP, serAddrTCP;
    char buffer[BUFSIZE];
public:
    Worker() = default;
    ~Worker() {
        close(cliSockDestUDP);
        close(cliSockDestTCP);
    }

    void init(){
        /*** Binding to the port UDP ***/
        if ((cliSockDestUDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("Server creation error UDP");
            exit(EXIT_FAILURE);
        }

        serAddrUDP.sin_family = AF_INET;
        serAddrUDP.sin_port = htons(PORT);
        serAddrUDP.sin_addr.s_addr = INADDR_ANY;
    }
    void initTCP(){
        /*** Binding to the port TCP ***/
        if ((cliSockDestTCP = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("Socket creation error TCP");
            exit(EXIT_FAILURE);
        }

        serAddrTCP.sin_family = AF_INET;
        serAddrTCP.sin_port = htons(PORT);
        serAddrTCP.sin_addr.s_addr = INADDR_ANY;

        if (connect(cliSockDestTCP, (struct sockaddr*)&serAddrTCP, sizeof(serAddrTCP)) < 0) {
            perror("\nConnection Failed \n");
        }
    }
    void recvMsg(){
        socklen_t cliAddrLen = sizeof(serAddrUDP);
        if (recvfrom(cliSockDestUDP, buffer, sizeof(buffer), 0, (struct sockaddr*)&serAddrUDP, &cliAddrLen) < 0) {
            perror("reading error...\n");
            close(cliSockDestUDP);
            exit(-1);
        }
    }
    void sendMsg(const std::string& msg){
        socklen_t cliAddrLen = sizeof(serAddrUDP);
        if (sendto(cliSockDestUDP, msg.c_str(), msg.length(), 0, (struct sockaddr*)&serAddrUDP, cliAddrLen) < 0) {
            perror("sending error...\n");
            close(cliSockDestUDP);
            exit(-1);
        }
    }

    void splitIdPort(std::string& str){
        std::vector<std::string> split;
        std::string delimiter = "/";
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;

        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
            token = str.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            split.push_back (token);
        }
        split.push_back(str.substr (pos_start));

        id = split.at(0);
        portRTC = std::stoi(split.at(1));
    }
    void setId(){
        sendMsg("");
        memset(buffer, 0, sizeof(buffer));
        recvMsg();
        std::string msg = buffer;
        splitIdPort(msg);
        std::cout << "My id: " << id << ", port for RPC: " << portRTC << std::endl;
        memset(buffer, 0, sizeof(buffer));
    }
    [[nodiscard]] bool getKickOut() const{
        return kickOut;
    }
    [[nodiscard]] int getPortRPC() const{
        return portRTC;
    }
    void setKickOut(){
        kickOut = !kickOut;
    }
    const char* getBuffer(){
        return buffer;
    }
    void healthCheck(){
        std::string msg = id + " Alive";
        sendMsg(msg);
        memset(buffer, 0, sizeof(buffer));
    }
    void sendToDatabase(int index, std::string& str){
        initTCP();
        Http http = Http();
        std::string temp = http.createPOST(std::to_string(index), str);
        send(cliSockDestTCP, temp.c_str(), temp.length(), 0);
        close(cliSockDestTCP);
        messageToDB.clear();
    }
}worker;

#include "RPCImp.h"

#endif //VSPRAKTIKUM_WORKER_H