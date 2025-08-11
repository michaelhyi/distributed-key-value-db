FROM michaelyi/dkvdb-base:latest

COPY protobufs/dkvdb.proto /usr/src/app/protobufs/dkvdb.proto
COPY dkvdb/ /usr/src/app/dkvdb/

RUN cd dkvdb/ \
    && rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make

RUN mv dkvdb/build/dkvdb /usr/local/bin/dkvdb \
    && rm -rf ./*

ENTRYPOINT [ "dkvdb" ]
