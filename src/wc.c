#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    return 1;
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    perror("Error opening file");
    return 1;
  }
  char buffer[1024];
  size_t lines = 0;
  size_t words = 0;
  size_t bytes = 0;
  ssize_t bytes_read = 0;
  int in_word = 0;
  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
  {
    bytes += bytes_read;
    for (int i = 0; i < bytes_read; i++)
    {
      if (isspace((unsigned char)buffer[i]))
      {
        if (in_word == 1)
        {
          in_word = 0;
          words++;
        }
      }
      else
      {
        if (in_word == 0)
        {
          in_word = 1;
        }
      }
      if (buffer[i] == '\n')
      {
        lines++;
      }
    }
  }
  if (in_word == 1)
  {
    words++;
  }
  if (bytes_read < 0)
  {
    perror("read");
    close(fd);
    return 1;
  }
  close(fd);
  printf("%zu\n", bytes);
  printf("%zu\n", lines);
  printf("%zu\n", words);

  return 0;
}
