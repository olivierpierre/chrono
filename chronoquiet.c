#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  struct timeval t1, t2;
  uint64_t ut1, ut2;
  int r_val, i, saved_stdout;
  char buffer[1024], stdout_path[20];
  
  if(argc < 2)
  {
    fprintf(stderr, "Usage : %s <command>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  saved_stdout = dup(STDOUT_FILENO);
  
  buffer[0] = '\0';
  for(i=1; i<argc; i++)
  {
    strcat(buffer, argv[i]);
    strcat(buffer, " ");
  }
  
  freopen("/dev/null", "w", stdout);
  
  if(gettimeofday(&t1, NULL))
  {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }
  
  r_val = system(buffer);
  if(r_val == -1)
  {
    perror("system");
    exit(EXIT_FAILURE);
  }
  
  if(gettimeofday(&t2, NULL))
  {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }
  
  ut1 = (uint64_t)t1.tv_sec * 1000000LLU + (uint64_t)t1.tv_usec;
  ut2 = (uint64_t)t2.tv_sec * 1000000LLU + (uint64_t)t2.tv_usec;
  
  sprintf(stdout_path, "/dev/fd/%d", saved_stdout);
  freopen(stdout_path, "w", stdout);

  printf("%lu\n", ut2-ut1);
  
  return EXIT_SUCCESS;
}
