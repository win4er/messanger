#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <assert.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 4040

void* listen_client(void* arg) {
    int id_client = *static_cast<int*>(arg);
    int buff_size = 64;
    char buffer[buff_size];
    int amount_recv;
    while (true) {
        memset(buffer, 0x00, buff_size);
        amount_recv = recv(id_client, buffer, buff_size, 0);
        if (amount_recv == 0) {
            std::cerr << "Connection with client#" << id_client;
            std::cerr << " is closed!" << std::endl;
            return nullptr;
        } else if (amount_recv < 0) {
            std::cerr << "Error with data receiving\n";
        }
        std::cout << "Message from client#" << id_client;
        std::cout << ": " << buffer << std::endl;
    }
    close(id_client);
    std::cout << "Client #" << id_client << "is closed" << std::endl;
    return nullptr;
}

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
    
    int client_sock;
    pthread_t id_thread;
    while (true) {
        client_sock = accept(server_sock, nullptr, nullptr);
        assert(client_sock > 0);
        pthread_create(&id_thread, nullptr, listen_client, &client_sock);
    }

    close(server_sock);
    std::cout << "Server is closed" << std::endl;
    return 0;
}
