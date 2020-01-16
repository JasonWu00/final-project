#include "networking.h"

void error_check( int i, char *s ) {
  if ( i < 0 ) {
    printf("[%s] error %d: %s\n", s, errno, strerror(errno) );
    exit(1);
  }
}

int client1setup() {
  int c1d = socket(AF_INET, SOCK_STREAM, 0);
  error_check( c1d, "client1 socket" );
  printf("[client1] socket created\n");
  //struct setup for getaddrinfo
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4 address
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  hints->ai_flags = AI_PASSIVE;  //Use all valid addresses
  getaddrinfo(NULL, PORT, hints, &results); //NULL means use local address
  //set socket to listen state
  i = listen(c1d, 10);
  error_check( i, "server listen" );
  printf("[server] socket in listen state\n");
  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  return c1d;
}

int client2setup(char * server) {
  int c2d, i;

  //create the socket
  c2d = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( c2d, "client 2 socket" );

  //run getaddrinfo
  /* hints->ai_flags not needed because the client
     specifies the desired address. */
  struct addrinfo * hints, * results;
  hints = (struct addrinfo *)calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;  //IPv4
  hints->ai_socktype = SOCK_STREAM;  //TCP socket
  getaddrinfo(server, PORT, hints, &results);

  //connect to the server
  //connect will bind the socket for us
  i = connect( c2d, results->ai_addr, results->ai_addrlen );
  error_check( i, "client connect" );

  free(hints);
  freeaddrinfo(results);

  return c2d;
}
