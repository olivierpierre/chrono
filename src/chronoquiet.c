#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
  struct timeval t1, t2;
  uint64_t ut1, ut2;
  int r_val, i;
  char buffer[1024];
  
  if(argc < 2)
  {
    fprintf(stderr, "Usage : %s <command>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  buffer[0] = '\0';
  for(i=1; i<argc; i++)
  {
    strcat(buffer, argv[i]);
    strcat(buffer, " ");
  }
  
  strcat(buffer, " &> /dev/null");
  
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

  printf("%llu\n", ut2-ut1);
  
  return EXIT_SUCCESS;
}
