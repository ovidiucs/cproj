#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strerror
#include <errno.h>  // errno
#include <netinet/in.h> // sockaddr_in
#include <assert.h> // for assert
#include <unistd.h> // for write to fd
#include <sys/types.h>
#include <sys/socket.h>

//#define PORT 6969


char response[] = 
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "\n"
        "<html>"
            "<head>"
            "<title>PHP is the BEST</title>"
            "</head>"
        "<body>"
            "<h1>PHP is the best</h1>"
        "</body>"
     "</html>";
// ----------------------------------------------------------------

int main (int argc, char **argv) {
      if (argc < 2) {
      fprintf(stderr, "Usage: %s <port>>\n", argv[0]);
      // Return error code
      exit(1);

     }
     uint16_t port = 0;

     {
        char *endptr;
        port = (uint16_t) strtoul(argv[1], &endptr, 10);

        if (endptr == argv[1]) {
            fprintf(stderr, "Invalid. %s is not a valid port number\n", argv[1]);
            exit(1);
        }
     }

    // 1. Create the socket
    int server_fd =  socket (AF_INET, SOCK_STREAM, 0);

    // 1.1 Check for errors
    if (server_fd < 0) {
        fprintf (stderr, "Could not create socket %s\n", strerror (errno));
        exit(1);
    }
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // 2. Bind the socket
    ssize_t err = bind (server_fd, (struct sockaddr*) &serverAddr, sizeof(serverAddr));
    if (err < 0) {
        fprintf (stderr, "Could not bind socket %s\n", strerror (errno));
        exit(1);
    }

    //3. Listen to socket
    // backlog - number of connection we want to support in queue
    err = listen(server_fd, 69);
    if (err < 0) {
        fprintf (stderr, "Could not listen to socket %s\n", strerror (errno));
        exit(1);
    }

    //4. Keep accepting connections
    // we will get back a file descriptor 
    for (;;) {

        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = 0;
        
        int client_fd = accept (server_fd,(struct sockaddr*) &clientAddr, &clientAddrLen);
        if (client_fd < 0 ){
            fprintf (stderr, "Could not accept connection from %s\n", strerror (errno));
            exit(1);
        }
        assert(clientAddrLen == sizeof(clientAddr));

        //write to file descriptor
        // response is array of chars not pointer to char. it can take the sizeof operator
        write(client_fd, response, sizeof(response));
        if (err < 0) {
            fprintf(stderr, "Could not send data %s\n", strerror(errno));
        }
        // close the connection
        err  = close(client_fd);
        if (err < 0) {
            fprintf(stderr, "Could not close client connection from %s\n", strerror(errno));
        }
    }

    return 0;
}

// ----------------------------------------------------------------
