#include <SFML/Network.hpp>
#include <iostream>
#include <string.h>

int main() {
    sf::TcpListener listener;
    if (listener.listen(53000) != sf::Socket::Done) {
        std::cerr << "Error: Could not listen on port 53000" << std::endl;
        return -1;
    }

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done) {
        std::cerr << "Error: Could not accept connection" << std::endl;
        return -1;
    }

    while (true) {
        // Receive data from the client
        char data[100];
        std::size_t received;
        if (client.receive(data, sizeof(data), received) != sf::Socket::Done) {
            std::cerr << "Error: Could not receive data" << std::endl;
            break;
        }

        // Process data and update game state
        std::cout << "Received: " << data << std::endl;

        // Send response to the client
        const char* response = "Update from server";
        if (client.send(response, strlen(response) + 1) != sf::Socket::Done) {
            std::cerr << "Error: Could not send data" << std::endl;
            break;
        }
    }

    return 0;
}
