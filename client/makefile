include makefile.inc

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

CLIENT_OUT=client


all: $(CLIENT_OUT) bin_move


$(CLIENT_OUT) : $(OBJECTS) 


%.o: %.c
	$(GCC) $(GCCFLAGS) -I./includes -c $< -o $@
	mkdir -p bin

bin_move:
	mv $(CLIENT_OUT) bin/


clean:
	rm -rf *.o client bin/