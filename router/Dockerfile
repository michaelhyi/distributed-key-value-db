FROM michaelyi/base:latest

COPY protobufs/db.proto /usr/src/app/protobufs/db.proto
COPY protobufs/router.proto /usr/src/app/protobufs/router.proto
COPY router/ /usr/src/app/router/

RUN cd router \
    && rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make

RUN mv router/build/router /usr/local/bin/router \
    && rm -rf ./*

ENTRYPOINT [ "router" ]
