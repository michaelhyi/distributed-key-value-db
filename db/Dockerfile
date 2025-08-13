FROM michaelyi/base:latest

COPY db/ /usr/src/app/db/
COPY protobufs/db.proto /usr/src/app/protobufs/db.proto
COPY protobufs/router.proto /usr/src/app/protobufs/router.proto

RUN cd db/ \
    && rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make

RUN mv db/build/db /usr/local/bin/db \
    && rm -rf ./*

ENTRYPOINT [ "db" ]
