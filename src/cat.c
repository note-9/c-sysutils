#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
  int fd = open("./test.txt", O_RDONLY);
  char buffer[1024];
  ssize_t n = read(fd, buffer, sizeof(buffer));
  printf("read %zd bytes\n", n);
  write(STDOUT_FILENO, buffer, n);
  close(fd);

  printf("fd = %d\n", fd);
  return 0;
}
