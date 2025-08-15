#include "shard_discovery.h"

#include <stdexcept>
#include <unordered_map>

void ShardDiscoveryService::add(std::shared_ptr<const Shard> shard) {
    if (!shard) {
        throw std::runtime_error("Shard must be non-null");
    }

    shards.insert(shard);
}

std::shared_ptr<const Shard> ShardDiscoveryService::get_shard(const std::string& key) const {
    if (shards.empty()) {
        throw std::runtime_error("No shards registered");
    }

    std::size_t hash = std::hash<std::string>{}(key);
    return shards[hash % shards.size()];
}
