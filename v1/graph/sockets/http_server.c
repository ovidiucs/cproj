#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strerror
#include <errno.h>  // errno
#include <netinet/in.h> // sockaddr_in
#include <assert.h> // for assert
#include <unistd.h> // for write to fd
#include <setjmp.h> // for jump
#include <sys/types.h>
#include <sys/socket.h>
#include "s.h"

// ----------------------------------------------------------------
// Credits: https://www.twitch.tv/tsoding

// ----------------------------------------------------------------

//#define PORT 6969
// Macros for data sizes
#define KILO 1024
#define MEGA (1024 * KILO)
#define GIGA (1024 * MEGA)
// Macro for a 640 kilobyte buffer
#define REQUEST_BUFFER_CAPACITY (640 * KILO)

// ----------------------------------------------------------------

int http_error(int code,const char *message);
void handleRequest(int fd);
void write_response(int fd, int code);
// set 640KB of char array

char requestBuffer[REQUEST_BUFFER_CAPACITY];

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

// save the jump point
jmp_buf handleRequestError;

void write_response(int fd, int code) {
    dprintf(fd,
        "HTTP/1.1 %d BLABLA\n"
        "Content-Type: text/html\n"
        "\n"
        "<html>"
            "<head>"
            "<title>Error code %d</title>"
            "</head>"
        "<body>"
            "<h1>Error code %d</h1>"
        "</body>"
    "</html>",
     code,code,code);
}
int http_error(int code, const char *message) {
    (void) code;
    fprintf (stderr, "%s\n",message);
    longjmp (handleRequestError,code);
}

// Request handler to write to stdout the request comming in
// from the web client. Takes a file descriptor.
void handleRequest(int fd) {

    ssize_t requestBufSize = read(fd, requestBuffer,REQUEST_BUFFER_CAPACITY);
    // If the allocation was succesfull the read syscall will return 0
    if (requestBufSize == 0) {
        http_error(400,"EOF");
    }
    if (requestBufSize < 0) {
        http_error(500, strerror(errno));
    }

    String buffer = {
        .len = (uint64_t) requestBufSize,
        .data = requestBuffer
    };

    String line = trim_end(chop_line(&buffer));
    if (!line.len) {
        http_error(400, "Empty status line");
    }

    String method = chop_word(&line);
    if (!string_equal(method, string_null("GET"))) {
        http_error(405,"Unknown method");
    }

    String path = chop_word(&line);
    if(!string_equal(path,string_null("/"))) {
        http_error(404,"Unknown path");
    }

}
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
        //does not unwind the stack
        int code = setjmp(handleRequestError);
        if (code == 0) {
            // try
            handleRequest(client_fd);
              // response is array of chars not pointer to char. it can take the sizeof operator
            err = write(client_fd, response, sizeof(response));
            if (err < 0) {
                fprintf(stderr, "Could not send data %s\n", strerror(errno));
            }
        } else {
            write_response(client_fd, code);
        }

        printf("------------------------------\n");

        err  = close(client_fd);
        // close the connection
        if (err < 0) {
            fprintf(stderr, "Could not close client connection from %s\n", strerror(errno));
        }
    }

    return 0;
}

// ----------------------------------------------------------------
