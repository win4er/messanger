#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

int main() {
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    std::string message = "Hello, server!";
    send(client_sock, message.c_str(), message.size(), 0);

    close(client_sock);
    return 0;
}
