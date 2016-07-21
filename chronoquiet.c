#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  struct timeval t1, t2;
  uint64_t ut1, ut2;
  int ret, i, child_ret;
  char **exec_line;
  pid_t pid;
  
  if(argc < 2)
  {
    fprintf(stderr, "Usage : %s <command>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /* Create array for execv */
  exec_line = (char **)malloc((argc) * sizeof(char *));
  for(i=1; i<argc; i++)
  {
	exec_line[i-1] = (char *)malloc((strlen(argv[i]) + 1) * sizeof(char));
	strcpy(exec_line[i-1], argv[i]);
  }
  exec_line[argc - 1] = NULL;
    
  if(gettimeofday(&t1, NULL))
  {
    perror("gettimeofday");
    goto err_free;
  }
  
  pid = vfork();
  if(pid == -1)
  {
	perror("vfork");
	goto err_free;
  }
  else if(pid == 0)
  {
	freopen("/dev/null", "w", stderr);
	freopen("/dev/null", "w", stdout);
    execvp(exec_line[0], exec_line);
    perror("child exec");
	exit(EXIT_FAILURE);
  }
  else
  { 
    ret = waitpid(pid, &child_ret, 0);
    
    if(gettimeofday(&t2, NULL))
    {
      perror("gettimeofday");
      goto err_free;
    }
    
    if(ret == -1)
    {
		perror("waitpid");
		goto err_free;
	}
	
    if(child_ret)
    {
        fprintf(stderr, "Error: child returned non zero exit status: %d\n", 
                WEXITSTATUS(child_ret));
        goto err_free;           
    }
  }
   
  ut1 = (uint64_t)t1.tv_sec * 1000000LLU + (uint64_t)t1.tv_usec;
  ut2 = (uint64_t)t2.tv_sec * 1000000LLU + (uint64_t)t2.tv_usec;
  
  printf("%lu\n", ut2-ut1);
  
  for(i=0; i<(argc-1); i++)
	free(exec_line[i]);
  free(exec_line);
  
  return EXIT_SUCCESS;

err_free:
  for(i=0; i<(argc-1); i++)
	free(exec_line[i]);
  free(exec_line);
  return EXIT_FAILURE;
}
