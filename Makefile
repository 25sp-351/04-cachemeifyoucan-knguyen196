CC = gcc
CFLAGS = -Wall -Wextra -g

all: rod_cutting_lru rod_cutting_lfu

rod_cutting_lru: main_lru.o cache_lru.o
	$(CC) $(CFLAGS) -o rod_cutting_lru main_lru.o cache_lru.o

rod_cutting_lfu: main_lfu.o cache_lfu.o
	$(CC) $(CFLAGS) -o rod_cutting_lfu main_lfu.o cache_lfu.o

main_lru.o: main.c cache.h
	$(CC) $(CFLAGS) -DLRU -c main.c -o main_lru.o

cache_lru.o: cache.c cache.h
	$(CC) $(CFLAGS) -DLRU -c cache.c -o cache_lru.o

main_lfu.o: main.c cache.h
	$(CC) $(CFLAGS) -DLFU -c main.c -o main_lfu.o

cache_lfu.o: cache.c cache.h
	$(CC) $(CFLAGS) -DLFU -c cache.c -o cache_lfu.o

clean:
	rm -f *.o rod_cutting_lru rod_cutting_lfu
