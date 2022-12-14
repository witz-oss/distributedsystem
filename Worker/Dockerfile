# image
FROM ubuntu:16.04

# Install C++
RUN apt-get update && \
    apt-get install -y \
        automake \
        bison \
        flex \
        g++ \
        git \
        libboost-all-dev \
        libevent-dev \
        libssl-dev \
        libtool \
        make \
        pkg-config \
        wget && \
    apt-get clean && \
    rm -rf /var/cache/apt/* && \
    rm -rf /var/tmp/* && \
    rm -rf /tmp/* && \
    rm -rf /var/lib/apt/lists/*

# Install Apache Thrift
RUN git clone --single-branch --branch 0.13.0 http://github.com/apache/thrift

RUN cd thrift && \
    ./bootstrap.sh && \
    ./configure && \
    make install && \
    ldconfig


# Compile
WORKDIR /worker
COPY . .

RUN make worker
CMD ["./Worker"]