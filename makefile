COMPILER = gcc       
COMPILER_FLAGS = -Wall -g -std=c99 -c
LINKER = gcc       
LIB = -lz

#======== for "make all" =========================================================================
all: file_io.out unix_processes.out

#======= for each executable, link together relevant object files and libraries==================
file_io.out: file_io.o
	$(LINKER) -o file_io.out file_io.o

unix_processes.out: unix_processes.o
	$(LINKER) -o unix_processes.out unix_processes.o

#======= for each object file, compile it from source  ===========================================
file_io.o: file_io.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o file_io.o file_io.c

unix_processes.o: unix_processes.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o unix_processes.o unix_processes.c

#======== for "make clean" ========================================================================
.PHONY: clean
clean:
	rm -f *.d *.o *.out *.txt