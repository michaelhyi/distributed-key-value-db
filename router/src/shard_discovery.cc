#include "shard_discovery.h"

#include <stdexcept>
#include <unordered_map>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <spdlog/spdlog.h>

#include "zookeeper_service.h"

std::shared_ptr<const Shard> ShardDiscoveryService::get_shard(const std::string& key) const {
    std::unordered_map<std::string, std::string> shard_znodes;

    try {
        shard_znodes = zookeeper_service.get_children("/shards");
    } catch (const std::exception& e) {
        spdlog::warn("Error getting znodes from zookeeper: {}", e.what());
    }

    std::vector<std::string> shards;
    shards.reserve(shard_znodes.size());

    if (shard_znodes.empty()) {
        throw std::runtime_error("No shards registered");
    }

    for (const std::pair<std::string, std::string>& pair : shard_znodes) {
        spdlog::debug("Server address {}", pair.second);
        shards.push_back(pair.second);
    }

    std::size_t hash = std::hash<std::string>{}(key);
    std::string server_address = shards[hash % shards.size()];
    std::shared_ptr<const Shard> shard(
        new Shard(
            grpc::CreateChannel(server_address + ":50051", grpc::InsecureChannelCredentials())
        )
    );

    return shard;
}
