
CC=gcc
 
CFLAGS = -Wall -g -D VERBOSE
OBJ = main.o matrix.o parmatmultcp.o tcp_comm.o

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

parmatmul: $(OBJ)
	$(CC) -o $@ $^ 

clean:
	rm -rf $(OBJ) parmatmul
