CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: main.exe

main.exe: main.c dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) main.c dijkstra.c -o main.exe

clean:
	rm -f main.exe