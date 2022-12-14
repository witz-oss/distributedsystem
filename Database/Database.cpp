#include "Database.h"

int main() try{

    Database database = Database();
    database.init();

    while(true) {
        database.listening();
    }

    return 0;
}catch(std::exception& e){
    std::cerr << e.what() << std::endl;
    return -1;
}catch(...){
    std::cerr << "some wrong" << std::endl;
    return -1;
}




