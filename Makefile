CC=gcc
CFLAGS=-std=c11 -Wall -o3

LIBS=-lm

MYC=envelope.h

envelope: $(MYC)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
