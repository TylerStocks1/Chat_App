#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int CreateSocket();

bool BindSocket(int socket, int port);

bool ListenSocket(int socket, int backlog);

int AcceptClient(int serverSocket);

bool ConnectToServer(int socket, const std::string &ip, int port);