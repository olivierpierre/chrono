# Chrono
Super simple program to record a command execution time. `chrono`  is the base program, and `chronoquiet` can be used to suppress the standard output of the measured command.

```shell
pierre@bulbi:~/chrono$ chrono ls
chrono	chrono.c  chrono.out  chronoquiet  chronoquiet.c  Makefile  README.md
1376
pierre@bulbi:~/chrono$ chronoquiet ls
1366
```
