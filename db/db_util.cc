#include "db_util.h"

#include <string>
#include <stdexcept>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <chrono>
#include <thread>

#include "router_client.h"
#include "network_util.h"

const int MAX_RETRIES = 5;
const int RETRY_DELAY_MS = 2000;

void DbUtil::register_node() {
    std::string server_address = NetworkUtil::get_server_address();

    RouterClient router_client(
        grpc::CreateChannel("router:80", grpc::InsecureChannelCredentials())
    );

    bool registered = false;
    for (int i = 0; i < MAX_RETRIES; i++) {
        try {
            router_client.RegisterNode(server_address);
            registered = true;
            break;
        } catch (const std::exception& e) {
            std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS));
        }
    }

    if (!registered) {
        throw std::runtime_error("Failed to register node");
    }
}
