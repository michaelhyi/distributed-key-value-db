#pragma once

template <typename... Services>
void RunServer(int port, Services*... services);

#include "server.tpp"
