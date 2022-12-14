cmake_minimum_required(VERSION 3.21)
project(DistributedSystem)

set(CMAKE_CXX_STANDARD 17)

# brew info thrift
set(THRIFT /opt/homebrew/Cellar/thrift/0.17.0)      # set the lib path
include_directories(${THRIFT}/include/)             # include the lib
link_directories(${THRIFT}/lib/)                    # link the lib


add_executable(DistributedSystem Server/Server.cpp Server/Server.h Worker/Worker.cpp Worker/Worker.h Worker/Http.h Database/Database.cpp Database/Database.h Database/Http.h Allgemein/Http/Http.cpp Allgemein/Http/Http.h Worker/RPCImp.h Worker/RPCImp.h)
