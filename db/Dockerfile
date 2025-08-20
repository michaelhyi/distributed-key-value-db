FROM michaelyi/base:latest

COPY db/ /usr/src/app/db/
COPY protobufs/db.proto /usr/src/app/protobufs/db.proto

RUN cd db/ \
    && rm -rf build \
    && mkdir -p build \
    && cd build \
    && cmake .. \
    && make \
    && ctest

RUN mv db/build/db /usr/local/bin/db \
    && rm -rf ./*

ENTRYPOINT [ "db" ]
