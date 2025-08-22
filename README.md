## Distributed Key-Value Database

This database will support horizontal scaling via sharding, replication, and
2-layer routing. Nodes will follow a CQRS architecture with eventual consistency
supported via Kafka. Nodes will communicate via gRPC and are thread-safe, and
the database can be interfaced via a CLI or SDKs.

### Architecture
![Architecture](.github/Architecture.png)

`shard-router`, `replica-router`, `replica`, and `replica-write-service`
services are horizontally scaled and load balanced.

### Tech Stack
- C++
- gRPC
- Kubernetes
- Kafka
- Zookeeper
- googletest
- Docker
- CMake
- Protobuf

### Quick Start

Prerequisites:
- Docker
- Minikube
- Kubectl

Start minikube and the database:
```bash
minikube start
chmod +x ./run.sh
./run.sh
```

Send gRPC requests to the database at `grpc://localhost:50051` using `protobufs/db.proto`.

### TODO
- [ ] Rename gRPC Service Classes
- [ ] Separate shard-router and replica-router
- [ ] Leader Election
- [ ] Sharding vs. Replication 
- [ ] Replica Write Service
- [ ] Eventual Consistency
- [ ] Input Validation
- [ ] Logging (spdlog classnames)
- [ ] Exceptions
- [ ] Unit Testing
- [ ] gdb
- [ ] Shard Ungraceful Removal Handling
- [ ] Check Channel Connectivity Before Registering Shard
- [ ] Durability -> Disk Backups
- [ ] SSL Termination
- [ ] Namespaces
- [ ] CLI
- [ ] SDKs
