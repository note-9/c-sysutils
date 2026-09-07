#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    perror("Error opening file");
    return 1;
  }
  char buffer[1024];
  ssize_t bytes_read; 
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
  {
    ssize_t bytes_written = 0;
    while (bytes_written < bytes_read)
    {
      ssize_t n = write(STDOUT_FILENO, buffer + bytes_written, bytes_read - bytes_written);
      if (n < 0)
      {
        perror("write");
        return 1;
      }
      bytes_written += n;
    }
  }
  if (bytes_read < 0)
  {
    perror("read");
    close(fd);
    return 1;
  }
  close(fd);

  return 0;
}
