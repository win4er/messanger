#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <assert.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 4040

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(server_sock > 0); 

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);
    
    std::cout << "Server is open: " << SERVER_ADDRESS;
    std::cout << ":" << SERVER_PORT << std::endl;

    size_t buf_size = 1024;
    char buffer[buf_size];
    int bytes_read;
    while (true) {
        int client_sock = accept(server_sock, nullptr, nullptr);
        memset(buffer, 0x00, buf_size);
        bytes_read = recv(client_sock, buffer, sizeof(buffer), 0);

        if (bytes_read == 0) {
            std::cerr << "Connection is closed!\n";
        } else if (bytes_read < 0) {
            std::cerr << "Error with data receiving\n";
        }
        std::cout << "Message from client: " << buffer << std::endl;
    }

    close(server_sock);
    std::cout << "Server is closed" << std::endl;
    return 0;
}
