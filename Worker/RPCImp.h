#ifndef DISTRIBUTEDSYSTEM_RPCIMP_H
#define DISTRIBUTEDSYSTEM_RPCIMP_H


class RPCTasksHandler : virtual public RPCTasksIf {
private:
    Matrix matrix;
public:
    RPCTasksHandler() {

    }

    bool assignMatrix(const Matrix& matrix) {
        this->matrix.id = matrix.id;
        this->matrix.matrixA = matrix.matrixA;
        this->matrix.matrixB = matrix.matrixB;

        return true;
    }

    bool calcMatrix(const Operation::type op) {
        //sleep(5);
        switch (op) {
            case Operation::ADD:
                for(int i = 0; i < matrix.matrixA.size(); i++) {
                    std::vector<int> temp;
                    for (int j = 0; j < matrix.matrixB.size(); j++)
                        temp.push_back(matrix.matrixA[i][j] + matrix.matrixB[i][j]);
                    matrix.matrixResult.push_back(temp);
                }
                return true;
            case Operation::SUBTRACT:
                for(int i = 0; i < matrix.matrixA.size(); i++) {
                    std::vector<int> temp;
                    for (int j = 0; j < matrix.matrixB.size(); j++)
                        temp.push_back(matrix.matrixA[i][j] - matrix.matrixB[i][j]);
                    matrix.matrixResult.push_back(temp);
                }
                return true;
            default:
                return false;
        }
    }

    void saveMatrix() {
        std::string msg;
        for(int i = 0; i < matrix.matrixResult.size(); i++) {
            msg += "≥\t";
            for(int j = 0; j < matrix.matrixResult.at(i).size(); j++) {
                msg += " " + std::to_string(matrix.matrixResult[i][j]) + "\t";
            }
            msg +=  "≤\n";
        }
        worker.sendToDatabase(this->matrix.id, msg);
        sleep(1);
    }

    void ping(const std::string& msg) {
        // Your implementation goes here
        std::cout << "ping: " << msg << std::endl;
    }

}rpcTasksHandler;


class RPCTasksCloneFactory : virtual public RPCTasksIfFactory {             // for poolThread services
public:
    ~RPCTasksCloneFactory() override = default;
    RPCTasksIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) override
    {
        std::shared_ptr<TProcessor> sock = std::dynamic_pointer_cast<TProcessor>(connInfo.transport);
        return new RPCTasksHandler;
    }
    void releaseHandler(RPCTasksIf* handler) override {
        delete handler;
    }
};

#endif //DISTRIBUTEDSYSTEM_RPCIMP_H
