#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
  
  int fd = open("file.txt", O_RDWR | O_CREAT);
  
  if (fd == -1) {
    printf("%s\n\n", strerror(errno));
  }

  char buf[256];
  int len = 1000;
  ssize_t op = read(fd, &buf, len);
  if (op == -1) {
    printf("%s\n\n", strerror(errno));
  }

  printf("%s\n", buf);

  char *buf2 = "Sie werde hier.\n";
  ssize_t nr = write(fd, buf2, strlen(buf2));
  if (nr == -1) {
    printf("%s\n\n", strerror(errno));
  }
  
  int closing = close(fd);
  
}
