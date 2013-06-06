#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#if EMSCRIPTEN
#include <emscripten.h>
#endif

int serverfd = -1;
int clientfd = -1;

void do_echo(int sockfd) {
  int n;
  char buffer[1024];
  struct sockaddr_in addr;
  socklen_t addrlen;

  // read the source data
  n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addrlen);
  if (n == -1 && errno != EAGAIN) {
    perror("recv failed");
    exit(EXIT_FAILURE);
  } else if (n <= 0) {
    return;
  }
  buffer[n] = 0;

  printf("recv'd \"%s\" (%d bytes)\n", buffer, n);

  // echo it back
  n = sendto(sockfd, buffer, n, 0, (struct sockaddr *)&addr, sizeof(addr));
  if (n == -1) {
    perror("send failed");
    exit(EXIT_FAILURE);
  }

  printf("echo'd back \"%s\" (%d bytes)\n", buffer, n);
}

void iter(void *arg) {
  int res;
  fd_set fdr;

  // see if there are any connections to accept / data to read
  FD_ZERO(&fdr);
  FD_SET(serverfd, &fdr);
#if !USE_UDP
  if (clientfd != -1) FD_SET(clientfd, &fdr);
#endif
  res = select(64, &fdr, NULL, NULL, NULL);
  if (res == -1) {
    perror("select failed");
    exit(EXIT_SUCCESS);
  }

  if (FD_ISSET(serverfd, &fdr)) {
    // for TCP sockets, this means there is a connection to accept
    // for UDP, it means we have data to read.
#if !USE_UDP
    // accept the incoming connection
    clientfd = accept(serverfd, NULL, NULL);
    assert(clientfd != -1);
#else
    do_echo(serverfd);
#endif
  }
#if !USE_UDP
  // for TCP sockets, we need to read data from the individual client socket.
  else if (FD_ISSET(clientfd, &fdr)) {
    do_echo(clientfd);
  }
#endif
}

int main() {
  struct sockaddr_in addr;
  int res;

#if !USE_UDP
  serverfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
  serverfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
  if (serverfd == -1) {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }
  fcntl(serverfd, F_SETFL, O_NONBLOCK);

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKK);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
    perror("inet_pton failed");
    exit(EXIT_FAILURE);
  }

  res = bind(serverfd, (struct sockaddr *)&addr, sizeof(addr));
  if (res == -1) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

#if !USE_UDP
  res = listen(serverfd, 50);
  if (res == -1) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }
#endif

#if EMSCRIPTEN
  emscripten_set_main_loop(iter, 60, 0);
#else
  while (1) iter(NULL);
#endif

  return EXIT_SUCCESS;
}
