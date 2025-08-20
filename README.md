## Distributed Key-Value Database

This database will support horizontal scaling via sharding, replication, and
2-layer routing. Nodes will follow a CQRS architecture with eventual consistency
supported via Kafka. Nodes will communicate via gRPC and are thread-safe, and
the database can be interfaced via a CLI or SDKs.

### Architecture
![Architecture](.github/Architecture.png)

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
- [ ] Subrouters: Leader Election, Sharding vs. Replication 
- [ ] Eventual Consistency
- [ ] Input Validation
- [ ] Logging
- [ ] Unit Testing
- [ ] Hash Ring Algorithm
- [ ] Check Channel Connectivity Before Registering Shard
- [ ] Durability -> Disk Backups
- [ ] SSL Termination
- [ ] Namespaces
- [ ] CLI
- [ ] SDKs
