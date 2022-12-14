FROM danger89/cmake
WORKDIR /database
COPY . .


RUN g++ -std=c++17 Database.cpp -o database

CMD ["./database"]

