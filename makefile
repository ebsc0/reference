COMPILER = gcc       
COMPILER_FLAGS = -Wall -g -std=c99 -c
LINKER = gcc       


#======== for "make all" =========================================================================
all: file_io.out #all executables should be listed here



#======= for each executable, link together relevant object files and libraries==================
#target: ingredients

file_io.out: file_io.o
	$(LINKER) -o file_io.out file_io.o -lz

#more executables ...
  
  
  
  
#======= for each object file, compile it from source  ===========================================
#target: ingredients
 
file_io.o: file_io.c common.h
	$(COMPILER) $(COMPILER_FLAGS) -o file_io.o file_io.c


#======== for "make clean" ========================================================================
.PHONY: clean
clean:
	rm -f *.d *.o *.out *.txt