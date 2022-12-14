CC=g++
LIBS=-lthrift -pthread
FLAGS=-std=c++17

GENSRC=gen-cpp/RPCTasks.cpp gen-cpp/RPCTasks_types.cpp

CLIENTSRC=Worker.cpp
SERVERSRC=Server.cpp
WORKER=Worker
SERVER=Server

$(WORKER): $(CLIENTSRC)
	$(CC) $(FLAGS) $(GENSRC) $(CLIENTSRC) -o $(WORKER) $(LIBS)

$(SERVER): $(SERVERSRC)
	$(CC) $(FLAGS) $(GENSRC) $(SERVERSRC) -o $(SERVER) $(LIBS)

server: $(SERVER)

worker: $(WORKER)

all: $(SERVER) $(WORKER)

clean:
	rm -rf $(GENSRC) $(WORKER) $(SERVER)
	
sterile: clean
	rm -rf gen-cpp/

