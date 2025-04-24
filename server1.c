#include <stdio.h>
#include <stdlib.h>
#include <string.h>      // for strlen()
#include <unistd.h>      // for close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

int main(){
    int sockid = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(2004);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockid, (struct sockaddr *)& server, sizeof(server));

    listen(sockid, 1);

    int connection = accept(sockid, NULL, NULL);

    char input[20];
    int flag = 1;
    int i, j;

    recv(connection, input, sizeof(input), 0);

    int n = strlen(input);

    if (n == 0) flag = 1;

    i = 0, j = n-1;

    while (i <= j)
    {
        if (input[i] == input[j]){
            ++i; --j;
        }
        else {
            flag = 0;
            break;
        }
    }

    send(connection, &flag, sizeof (int), 0);
    close(connection);
    close(sockid);
}