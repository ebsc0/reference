COMPILER = gcc       
COMPILER_FLAGS = -Wall -g -std=c99 -c
LINKER = gcc       
LIB = -lz -lcurl

# make all
all: \
	file_io.out \
	fork.out \
	signal_handling.out \
	mailbox.out \
	socket_client.out \
	socket_server.out \
	curl.out \
	pipes.out \
	threads.out \
	mutex.out \
	rendezvous.out \


# link object file(s) and librarie(s) and create executable
file_io.out: file_io.o
	$(LINKER) -o file_io.out file_io.o

fork.out: fork.o
	$(LINKER) -o fork.out fork.o

signal_handling.out: signal_handling.o
	$(LINKER) -o signal_handling.out signal_handling.o

mailbox.out: mailbox.o
	$(LINKER) -o mailbox.out mailbox.o

socket_client.out: socket_client.o
	$(LINKER) -o socket_client.out socket_client.o

socket_server.out: socket_server.o
	$(LINKER) -o socket_server.out socket_server.o

curl.out: curl.o
	$(LINKER) -o curl.out curl.o $(LIB)

pipes.out: pipes.o
	$(LINKER) -o pipes.out pipes.o
	
threads.out: threads.o
	$(LINKER) -o threads.out threads.o
	
mutex.out: mutex.o
	$(LINKER) -o mutex.out mutex.o

rendezvous.out: rendezvous.o
	$(LINKER) -o rendezvous.out rendezvous.o

# compile object file from source file(s)
file_io.o: file_io.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o file_io.o file_io.c

fork.o: fork.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o fork.o fork.c

signal_handling.o: signal_handling.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o signal_handling.o signal_handling.c

mailbox.o: mailbox.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o mailbox.o mailbox.c

socket_client.o: socket_client.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o socket_client.o socket_client.c

socket_server.o: socket_server.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o socket_server.o socket_server.c

curl.o: curl.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o curl.o curl.c

pipes.o: pipes.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o pipes.o pipes.c

threads.o: threads.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o threads.o threads.c

mutex.o: mutex.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o mutex.o mutex.c

rendezvous.o: rendezvous.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o rendezvous.o rendezvous.c

# make clean
.PHONY: clean
clean:
	rm -f *.d *.o *.out *.txt