CC=gcc
CFLAGS=-Wall
LDFLAGS=

all: chrono chronoquiet

chrono: chrono.c
	$(CC) $(CFLAGS) $^ -o $@

chronoquiet: chronoquiet.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o chrono chronoquiet

install: all
	cp -f chrono /usr/local/bin
	cp -f chronoquiet /usr/local/bin

uninstall:
	rm -f /usr/local/bin/chrono
	rm -f /usr/local/bin/chronoquiet
