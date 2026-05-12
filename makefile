CC = mpicc
CFLAGS = -Wall -O3 -g
BINS = main

all: $(BINS)

main: main.c utils.h utils.c prop.h prop.c
	$(CC) $(CFLAGS) -o main main.c utils.c prop.c

clean:
	$(RM) $(BINS)
	rm -rf *.dSYM
