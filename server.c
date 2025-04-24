#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // for strlen()
#include <unistd.h>      // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

// socket creation in server
int main() {
    int sersockD;
    sersockD = socket(AF_INET, SOCK_STREAM, 0);  // TCP socket

    // define server address
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(9001);                // Port 9001 (converted to network byte order)
    serAddr.sin_addr.s_addr = INADDR_ANY;          // Accept connections on all interfaces (0.0.0.0)

    // bind socket to IP & port
    bind(sersockD, (struct sockaddr*)&serAddr, sizeof(serAddr));

    // listen for connections, max 1 pending connection in the queue
    listen(sersockD, 1);

    // accept a client connection
    int clientSocket;
    clientSocket = accept(sersockD, NULL, NULL);

    char b1[20];
    int left, right, flag;

    // receive, check palindrome, send result
    for (;;) {
        recv(clientSocket, b1, sizeof(b1), 0);   // Receive string from client
        printf("\nThe string received is: %s\n", b1);

        if (strlen(b1) == 0) {
            flag = 1;
        } else {
            left = 0;
            right = strlen(b1) - 1;
            flag = 1;

            while (left < right) {
                if (b1[left] != b1[right]) {
                    flag = 0;
                    break;
                }
                left++;
                right--;
            }
        }

        send(clientSocket, &flag, sizeof(int), 0);  // Send result back to client
        break;
    }

    close(clientSocket);  // Close client socket
    close(sersockD);      // Close server socket
    return 0;
}
