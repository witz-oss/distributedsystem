#include "Worker.h"

void *thrift([[maybe_unused]] void *arg) {
    Worker worker = *(Worker*)arg;

    /*const int workerCount = 2;
    std::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(workerCount);
    threadManager->threadFactory(std::make_shared<ThreadFactory>());
    threadManager->start();

    TThreadPoolServer server(
            std::make_shared<RPCTasksProcessorFactory>(std::make_shared<RPCTasksCloneFactory>()),
            std::make_shared<TServerSocket>(9090),
            std::make_shared<TBufferedTransportFactory>(),
            std::make_shared<TBinaryProtocolFactory>(),
            threadManager);*/

    ::std::shared_ptr<RPCTasksHandler> handler(&rpcTasksHandler);
    ::std::shared_ptr<TProcessor> processor(new RPCTasksProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(worker.getPortRPC()));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();

    return nullptr;
}

void *workUDP(void *arg){
    Worker worker = *(Worker*)arg;
    while(worker.getKickOut()){
        worker.recvMsg();
        switch (worker.getBuffer()[0]) {
            case 'H':
                worker.healthCheck();
                break;
            case 'S':
                worker.setKickOut();
                break;
            default:
                std::cout << "Only H or S as first item !!";
                break;
        }
    }
    return nullptr;
}



int main() try {

    worker.init();
    worker.setId();

    pthread_t threadWorkUDP;
    pthread_t threadThrift;

    pthread_create(&threadWorkUDP, nullptr, &workUDP, &worker);
    pthread_create(&threadThrift, nullptr, &thrift, &worker);

    pthread_join(threadWorkUDP, nullptr);
    pthread_join(threadThrift, nullptr);

    return 0;

} catch(std::exception& e) {
    std::cout << e.what();
    return -1;
} catch (...) {
    std::cout << "some wrong";
    return -1;
}










