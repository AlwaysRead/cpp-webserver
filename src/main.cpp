#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    perror("socket");
    return 1;
  }

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(server_fd, (sockaddr *)&addr, sizeof(addr));
  listen(server_fd, 10);

  std::cout << "Server running on port 8080...\n";

  while (true) {
    int client = accept(server_fd, nullptr, nullptr);
    char buffer[4096];
    recv(client, buffer, sizeof(buffer), 0);

    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n\r\n"
                           "<h1>Hello from C++ Web Server</h1>";

    send(client, response, strlen(response), 0);
    close(client);
  }
}
