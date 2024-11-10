#include <SFML/Network.hpp>
#include <iostream>
#include <string.h>

int main() {
    sf::TcpSocket socket;
    if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done) {
        std::cerr << "Error: Could not connect to server" << std::endl;
        return -1;
    }

    // Send some data to the server
    const char* message = "Hello, server!";
    if (socket.send(message, strlen(message) + 1) != sf::Socket::Done) {
        std::cerr << "Error: Could not send data" << std::endl;
        return -1;
    }

    // Receive a response from the server
    char data[100];
    std::size_t received;
    if (socket.receive(data, sizeof(data), received) != sf::Socket::Done) {
        std::cerr << "Error: Could not receive data" << std::endl;
        return -1;
    }

    std::cout << "Received: " << data << std::endl;

    return 0;
}
