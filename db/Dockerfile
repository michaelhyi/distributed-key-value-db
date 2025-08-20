FROM michaelyi/base:latest

RUN apt-get update && apt-get install -y \
    libzookeeper-mt-dev \
    libzookeeper-mt2 \
    && rm -rf /var/lib/apt/lists/*

COPY db/ /usr/src/app/db/
COPY protobufs/db.proto /usr/src/app/protobufs/db.proto
COPY protobufs/router.proto /usr/src/app/protobufs/router.proto

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
