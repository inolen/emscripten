#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#if EMSCRIPTEN
#include <emscripten.h>
#endif

int sockfd = -1;
int connected = 0;
struct sockaddr_in local_addr;
struct sockaddr_in remote_addr;

void finish(int result) {
  close(sockfd);
#if EMSCRIPTEN
  REPORT_RESULT();
#endif
  exit(result);
}

void iter() {
  struct sockaddr_in addr;
  socklen_t addrlen = sizeof(struct sockaddr_in);
  int res;

  if (!connected) {
    // make sure that sockfd has finished connecting
    res = connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(remote_addr));
    if (res == -1 && errno != EINPROGRESS && errno != EALREADY && errno != EISCONN) {
      perror("connect failed");
      finish(EXIT_FAILURE);
    } else if (res == 0 || (res == -1 && errno == EISCONN)) {
      connected = 1;
    } else {
      return;
    }
  }
  
  // sockname should match the bound address for UDP sockets,
  // but currently we don't have any way to know what it should
  // match for TCP sockets.
  res = getsockname(sockfd, (struct sockaddr *)&addr, &addrlen);
  if (res != 0 ||
#if !USE_UDP
      0  // we should be doing something once this is supported in emscripten
#else 
      addr.sin_family != local_addr.sin_family ||
      addr.sin_addr.s_addr != local_addr.sin_addr.s_addr ||
      addr.sin_port != local_addr.sin_port
#endif
      ) {
    fprintf(stderr, "getsockname invalid result (res: %d, sin_family: %d, sin_addr: %d, sin_port: %d)\n", res, addr.sin_family, addr.sin_addr.s_addr, addr.sin_port);
    finish(EXIT_FAILURE);
  }

  // peername should match the address info we connected to
  res = getpeername(sockfd, (struct sockaddr *)&addr, &addrlen);
  if (res != 0 ||
      addr.sin_family != remote_addr.sin_family ||
      addr.sin_addr.s_addr != remote_addr.sin_addr.s_addr ||
      addr.sin_port != remote_addr.sin_port) {
    fprintf(stderr, "getpeername invalid result (res: %d, sin_family: %d, sin_addr: %d, sin_port: %d)\n", res, addr.sin_family, addr.sin_addr.s_addr, addr.sin_port);
    finish(EXIT_FAILURE);
  }

  finish(EXIT_SUCCESS);
}

int main() {
  struct sockaddr_in addr;
  socklen_t addrlen;
  int res;

  memset(&local_addr, 0, sizeof(local_addr));
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = 16777343;  // 127.0.0.1
  local_addr.sin_port = htons(1234);

  memset(&remote_addr, 0, sizeof(remote_addr));
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_addr.s_addr = 16777343;  // 127.0.0.1
  remote_addr.sin_port = htons(SOCKK);

  // initialize the socket
#if !USE_UDP
  sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
  sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#endif
  if (sockfd == -1) {
    perror("cannot create socket");
    finish(EXIT_FAILURE);
  }
  fcntl(sockfd, F_SETFL, O_NONBLOCK);
  
  // test when unconnected
  res = getsockname(sockfd, (struct sockaddr *)&addr, &addrlen);
  if (res != 0) {
    perror("getsockname should not fail when not connected");
    finish(EXIT_FAILURE);
  }

  res = getpeername(sockfd, (struct sockaddr *)&addr, &addrlen);
  if (res != -1 || errno != ENOTCONN) {
    fprintf(stderr, "getpeername should error out when not connected\n");
    finish(EXIT_FAILURE);
  }

#if USE_UDP
  // bind the UDP socket before connecting
  res = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));
  if (res == -1) {
    perror("bind failed");
    finish(EXIT_FAILURE);
  }
#endif

#if EMSCRIPTEN
  emscripten_set_main_loop(iter, 0, 0);
#else
  while (1) iter();
#endif

  return EXIT_SUCCESS;
}