CC = mpicc
CFLAGS = -Wall -O3 -g
BINS = main

all: $(BINS)

main: main.c gillespie.h gillespie.c prop.h prop.c
	$(CC) $(CFLAGS) -o main main.c gillespie.c prop.c

clean:
	$(RM) $(BINS)
	rm -rf *.dSYM
