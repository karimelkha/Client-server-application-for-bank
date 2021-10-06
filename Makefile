CC=gcc
CCFLAGS= -Wall -Werror 
LIBFLAGS=-lpthread -lm
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
TST_DIR=tests/
TST= $(wildcard $(TST_DIR)/*.cc)
OBJ_TEST = $(filter-out main.o, $(OBJ)) $(TST:.c=.o)
EXECS=server client
BSL=./businessLogic/
OPT=-g -Wall -pedantic 
all: $(EXECS)

clean: 
	rm -rf *.o vgcore* $(EXECS)

client: Client/client.c $(BSL)accounts.c
	$(CC) $(OPT) $(LIBFLAGS) $^ -o $@  

server: Server/server.c ${BSL}customers.c ${BSL}accounts.c
	$(CC) $(OPT) $(LIBFLAGS) $^ -o $@  
	
