## Distributed Key-Value Database

This database will support horizontal scaling via sharding, replication, and
routing. Nodes will follow a CQRS architecture with eventual consistency
supported via Kafka. Nodes will communicate via gRPC, and the database can be
interfaced via a CLI or SDKs.

### Tech Stack
- C++
- gRPC
- Kubernetes
- Kafka
- Docker
- CMake
- Protobuf

### Quick Start

Prerequisites:
- Docker
- Minikube
- Kubectl

Start minikube and point your terminal's Docker CLI to minikube's engine.
```bash
minikube start
eval $(minikube docker-env)
```

Build the base image and the images of each service.
```bash
docker build -f Dockerfile.base . -t michaelyi/base:latest
docker build -f db/Dockerfile . -t michaelyi/db:latest
docker build -f router/Dockerfile . -t michaelyi/router:latest
```
