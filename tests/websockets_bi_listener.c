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
#include <time.h>
#include <sys/ioctl.h>
#include <assert.h>
#if EMSCRIPTEN
#include <emscripten.h>
#endif

#define EXPECTED_BYTES 28

int listenfd = -1;
int sockfd = -1;
int sent = 0;
int sentTime = 0;

void finish(int result) {
#if EMSCRIPTEN
    REPORT_RESULT();
#endif
    exit(result);
}

unsigned int get_all_buf(int sock, char* output, unsigned int maxsize) {
  int bytes;
  if (ioctl(sock, FIONREAD, &bytes)) return 0;
  if (bytes == 0) return 0;

  char buffer[1024];
  int n;
  unsigned int offset = 0;
  while((errno = 0, (n = recv(sock, buffer, sizeof(buffer), 0))>0) ||
    errno == EINTR) {
    if(n > 0) {
      if (((unsigned int) n)+offset > maxsize) {
        fprintf(stderr, "too much data!");
        finish(EXIT_FAILURE);
      }
      memcpy(output+offset, buffer, n);
      offset += n;
    }
  }

  if(n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
    fprintf(stderr, "error in get_all_buf!");
    finish(EXIT_FAILURE);
  }
  return offset;
}

void iter(void *arg) {
  static char out[1024*2];
  static int pos = 0;
  struct sockaddr_in addr;
  socklen_t temp;
  fd_set fdr;
  fd_set fdw;
  int res;

  FD_ZERO(&fdr);
  FD_ZERO(&fdw);
  FD_SET(listenfd, &fdr);
  if (sockfd != -1) FD_SET(sockfd, &fdw);
  res = select(64, &fdr, &fdw, NULL, NULL);
  if (res == -1) {
    perror("select failed");
    finish(EXIT_SUCCESS);
  }

  if (FD_ISSET(listenfd, &fdr)) {
    // accept the incoming connection
    sockfd = accept(listenfd, (struct sockaddr *)&addr, &temp);
    assert(sockfd != -1);
    printf("accept..\n");
  }
  else if (FD_ISSET(sockfd, &fdw) && !sent) {
    // incoming connection is ready to write.. do so
    char data[] = "hello from the other siide\n";

    printf("send..\n");
    res = send(sockfd, data, sizeof(data), 0);
    if (res == -1) {
      if (errno != EAGAIN) {
        perror("send error");
        finish(EXIT_FAILURE);
      }
      return;
    }

    sent = 1;
    sentTime = clock();
  }
  // wait a second to close down the server
  else if (sentTime && (clock() - sentTime) > 1000) {
    finish(EXIT_SUCCESS);
  }
}

int main() {
  struct sockaddr_in addr;
  int res;

  listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listenfd == -1) {
    perror("cannot create socket");
    finish(EXIT_FAILURE);
  }
  fcntl(listenfd, F_SETFL, O_NONBLOCK);

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(SOCKK);
  if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) != 1) {
    perror("inet_pton failed");
    finish(EXIT_FAILURE);
  }

  printf("bind..\n");

  if (bind(listenfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("bind failed");
    finish(EXIT_FAILURE);
  }

  printf("listen.. %d\n", listenfd);

  if (listen(listenfd, 50) == -1) {
    perror("listen failed");
    finish(EXIT_FAILURE);
  }

#if EMSCRIPTEN
  emscripten_set_main_loop(iter, 60, 0);
#else
  while (1) iter(NULL);
#endif

  return EXIT_SUCCESS;
}
