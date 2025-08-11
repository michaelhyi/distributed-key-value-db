FROM michaelyi/dkvdb-base:latest

COPY protobufs/dkvdb_router.proto /usr/src/app/protobufs/dkvdb_router.proto
COPY dkvdb-router/ /usr/src/app/dkvdb-router/

RUN cd dkvdb-router \
    && rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make

RUN mv dkvdb-router/build/dkvdb_router /usr/local/bin/dkvdb_router \
    && rm -rf ./*

ENTRYPOINT [ "dkvdb_router" ]
