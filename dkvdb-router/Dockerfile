FROM gcc

WORKDIR /usr/src/app

ENV MY_INSTALL_DIR=/root/.local \
    PATH=/root/.local/bin:$PATH

RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    autoconf \
    libtool \
    pkg-config \
    libspdlog-dev \
    git \
    grep \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --recurse-submodules -b v1.74.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc \
    && cd grpc \
    && mkdir -p cmake/build \
    && cd cmake/build \ 
    && cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_CXX_STANDARD=17 \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../.. \
    && make -j 4 \
    && make install

COPY . .

RUN rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make

RUN mv build/dkvdb_router /usr/local/bin/dkvdb_router \
    && rm -rf ./*

ENTRYPOINT [ "dkvdb_router" ]
