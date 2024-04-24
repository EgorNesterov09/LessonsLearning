#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 12345;
const int BUFFER_SIZE = 1024;

int main() {
    // Создаем сокет
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Unable to create socket\n";
        return 1;
    }

    // Настраиваем адрес сервера
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Привязываем сокет к адресу
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Unable to bind socket\n";
        return 1;
    }

    // Начинаем слушать соединения
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error: Unable to listen on socket\n";
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    // Бесконечный цикл для принятия клиентских подключений
    while (true) {
        // Принимаем новое соединение
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::cerr << "Error: Unable to accept connection\n";
            continue;
        }

        std::cout << "New client connected\n";

        // Обработка сообщений от клиента
        char buffer[BUFFER_SIZE];
        while (true) {
            // Принимаем сообщение от клиента
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived < 0) {
                std::cerr << "Error: Unable to receive data\n";
                break;
            } else if (bytesReceived == 0) {
                std::cout << "Client disconnected\n";
                break;
            }

            // Выводим полученное сообщение
            buffer[bytesReceived] = '\0';
            std::cout << "Received message from client: " << buffer << std::endl;

            // Отправляем подтверждение о получении
            const char* response = "Message received";
            int bytesSent = send(clientSocket, response, strlen(response), 0);
            if (bytesSent < 0) {
                std::cerr << "Error: Unable to send response\n";
                break;
            }
        }

        // Закрываем соединение с клиентом
        close(clientSocket);
    }

    // Закрываем серверный сокет
    close(serverSocket);

    return 0;
}
