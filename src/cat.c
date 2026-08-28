#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
  int fd1 = open("./test.txt", O_RDONLY);
  int fd2 = open("./test.txt", O_RDONLY);
  close(fd1);
  close(fd2);

  printf("fd1 = %d\n", fd1);
  printf("fd2 = %d\n", fd2);
  return 0;
}
