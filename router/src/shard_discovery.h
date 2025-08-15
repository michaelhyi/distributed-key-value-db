#pragma once

#include <memory>
#include <string>

#include "shard.h"
#include "indexed_set.h"

class ShardDiscoveryService {
private:
    IndexedSet<std::shared_ptr<const Shard>> shards;

public:
    void add(std::shared_ptr<const Shard> shard);
    std::shared_ptr<const Shard> get_shard(const std::string& key) const;
};
