FROM michaelyi/base:latest

COPY router/ /usr/src/app/router/
COPY protobufs/db.proto /usr/src/app/protobufs/db.proto

RUN cd router \
    && rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make \
    && ctest

RUN mv router/build/router /usr/local/bin/router \
    && rm -rf ./*

ENTRYPOINT [ "router" ]
