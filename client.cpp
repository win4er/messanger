#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <assert.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 4040

int main() {
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(client_sock > 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    int connection = connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    assert(connection == 0);

    std::cout << "Connected to " << SERVER_ADDRESS;
    std::cout << ":" << SERVER_PORT << std::endl;
    
    std::string message;
    while (std::getline(std::cin, message)) {
        send(client_sock, message.c_str(), message.size(), 0);
    }
    close(client_sock);
    std::cout << "Client is closed" << std::endl;
    return 0;
}
