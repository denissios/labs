#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    // �������� ���������� ��������� ������
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    // ��������� ������ ������� �� ���������� ��������� ������
    char* hostname = argv[1]; // ��� ����� ��� IP-����� �������
    int port = atoi(argv[2]); // ���� ��� ����� � ��������

    // �������� ������
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock == -1) {
        perror("Error with socket!");
        exit(1);
    }

    // ����������� ������ � ������ �������
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, hostname, &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid hostname or IP address\n");
        exit(1);
    }
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error with connect!");
        exit(1);
    }

    char* command = "generate"; // ������� ��� ��������� ������
    if (write(client_sock, command, strlen(command) + 1) != strlen(command) + 1) {
        perror("write");
        exit(1);
    }

    // ��������� ���������� ������ �������
    char buffer[1024]; // ����� ��� �������� ����������
    int n = read(client_sock, buffer, sizeof(buffer)); // ���������� ����������� ����
    if (n == -1) {
        perror("read");
        exit(1);
    }

    // ����� ���������� ������ ������� �� �����
    printf("%s\n", buffer);

    // �������� ������
    close(client_sock);

    return 0;
}
