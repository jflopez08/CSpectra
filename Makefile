IDIR=.
CC=gcc
CFLAGS=-std=c11 -Wall -o3$(IDIR)

ODIR=obj
LIBS=-lm

MYOBJ=envelope.o
OBJ = $(patsubst %,$(ODIR)/%,$(MYOBJ))

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

envelope: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
