#include "Server.h"

void *createMatrix([[maybe_unused]] void *arg){
    int makeId = 0;
    while (true) {
        try {
            Matrix matrix;
            matrix.id = makeId++;

            for (int i = 0; i < 25; ++i) {
                std::vector<int> temp;
                for (int j = 0; j < 25; ++j)
                    temp.push_back(rand() % 20 + 1);
                matrix.matrixA.push_back(temp);
            }
            for (int i = 0; i < 25; ++i) {
                std::vector<int> temp;
                for (int j = 0; j < 25; ++j)
                    temp.push_back(rand() % 20 + 1);
                matrix.matrixB.push_back(temp);
            }
            pthread_mutex_lock(&mutex);
            matrixVec.push_back(matrix);
            pthread_mutex_unlock(&mutex);
        }catch (std::exception& e){
            std::cout << e.what();
        }
        sleep(1);
    }
    return nullptr;
}

void *healthCheck(void *arg){
    Server server = *(Server*)arg;
    while(true){
        try {
            sleep(10);
            server.healthCheck();
        }catch(std::exception& e){
            std::cout << e.what();
        }
    }
    return nullptr;
}


void* thriftClient(void* item) {
    Client client = *(Client*)item;
    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());    //for random bool
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    double t1 = 1.0e6 * (double) tv.tv_sec + tv.tv_usec;

    try {
        ::std::shared_ptr<TTransport> socket(new TSocket(inet_ntoa(client.cliSock.sin_addr), client.port));
        ::std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        ::std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        RPCTasksClient rpcClient(protocol);

        transport->open();

        if (rpcClient.assignMatrix(client.matrix)) {
            if (gen()) {
                if (rpcClient.calcMatrix(Operation::ADD)) {
                    pthread_mutex_lock(&mutex);
                    rpcClient.saveMatrix();
                    client.isBusy = false;
                    client.matrix.id = -1;
                    pthread_mutex_unlock(&mutex);
                }
            } else {
                if (rpcClient.calcMatrix(Operation::SUBTRACT)) {
                    pthread_mutex_lock(&mutex);
                    rpcClient.saveMatrix();
                    client.isBusy = false;
                    client.matrix.id = -1;
                    pthread_mutex_unlock(&mutex);
                }
            }
        }
        transport->close();
    } catch (std::exception &e) {
        std::cout << e.what();
    }

    gettimeofday(&tv, nullptr);
    double t2 = 1.0e6 * (double) tv.tv_sec + tv.tv_usec;
    std::cout << "\nRound-Trip-Time(RPC " << client.id << "): " << (t2 - t1) << std::endl;
}

int main() try {

    Server server;
    server.init();
    server.setIDClients();
    server.initTimeout();

    pthread_t threadHealthCheck;
    pthread_t threadCreateMatrix;
    pthread_t threadThrift[server.getCliAddrVec().size()];

    pthread_create(&threadHealthCheck, nullptr, &healthCheck, &server);
    pthread_create(&threadCreateMatrix, nullptr, &createMatrix, nullptr);

    while(true){
        for (auto& item:server.getCliAddrVec()) {
            if(!matrixVec.empty()) {
                if (!item.isBusy && !item.isDead) {
                    item.isBusy = true;
                    item.matrix = matrixVec.front();
                    matrixVec.pop_back();
                    pthread_create(&threadThrift[item.id], nullptr, &thriftClient, &item);
                    sleep(1);
                }
            }
        }
    }

    return 0;
} catch(std::exception& e) {
    std::cout << e.what();
    return -1;
} catch(...) {
    std::cout << "some wrong";
    return -1;
}
