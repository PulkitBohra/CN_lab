#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>        // for close()
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int sockD;
    sockD = socket(AF_INET, SOCK_STREAM, 0);  // Create socket

    // Server address struct
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(9001);                 // Port to connect to
    serAddr.sin_addr.s_addr = INADDR_ANY;           // Server IP (localhost / 0.0.0.0)

    // Connect to the server
    int connectstatus = connect(sockD, (struct sockaddr*)&serAddr, sizeof(serAddr));
    if (connectstatus == -1) {
        printf("Connection failed!\n");
        return 1;
    }

    int flag;
    char buffer[20];

    for (;;) {
        printf("\nEnter a string to check palindrome: ");
        scanf("%s", buffer);

        printf("\nClient: %s", buffer);

        send(sockD, buffer, sizeof(buffer), 0);          // Send string to server
        recv(sockD, &flag, sizeof(int), 0);             // Receive result from server

        if (flag == 1) {
            printf("\nServer: The string is a Palindrome.\n");
        } else {
            printf("\nServer: The string is not a palindrome.\n");
        }

        break;  // Exit after one check
    }

    close(sockD);   // Close socket
    return 0;
}