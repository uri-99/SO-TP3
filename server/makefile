include makefile.inc

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

SERVER_OUT=server


all: $(SERVER_OUT) bin_move


$(SERVER_OUT) : $(OBJECTS) -lm


%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@ 
	mkdir -p bin

bin_move:
	mv $(SERVER_OUT) bin/


clean:
	rm -rf *.o server bin/