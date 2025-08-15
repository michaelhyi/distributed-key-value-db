#pragma once

template <typename... Services>
void RunServer(unsigned int port, Services*... services);

#include "server.tpp"
