#!/usr/bin/env bash
set -euo pipefail

eval $(minikube docker-env)

docker build -f Dockerfile.base . -t michaelyi/base:latest
docker build -f db/Dockerfile . -t michaelyi/db:latest
docker build -f router/Dockerfile . -t michaelyi/router:latest

kubectl delete --all statefulset
kubectl delete --all svc 
kubectl delete --all deployment
kubectl delete --all pods 

kubectl apply -f k8s/
kubectl wait --for=condition=ready pod -l app=zookeeper --timeout=120s
kubectl wait --for=condition=ready pod -l app=router --timeout=120s
kubectl port-forward svc/router 50051:80
