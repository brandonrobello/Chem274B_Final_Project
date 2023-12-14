# This makefile creates objects from sorting functions in C++ after
# creation the object files, these are archive in a static library

# GNU C++ Compiler
CPP         = g++      # C++ Compiler

# Compiler flags -g debug, -O3 optimized version -c create a library object
CPPFLAGS    = -std=c++20 -g -O0 -c

# The directory where the include files needed to create the library objects are
INC_DIR = ../../Include

# The directory where all object files are going to be moved after creation
LIB_DIR = ../../Lib

# Linkable object files containing COVID CA
CA_OBJS = COVID_CA.o

# Sorting library containing sorting algorithms
CA_LIB = libmyCOVID.a

COVID_CA.o: COVID_CA.cpp $(INC_DIR)/COVID.h
	$(CPP) $(CPPFLAGS) COVID_CA.cpp -I$(INC_DIR)

# The following target creates a static library
libmyCOVID.a: $(CA_OBJS)
	ar ru $(CA_LIB) $(CA_OBJS)
	mv $(CA_LIB) $(LIB_DIR)
	rm $(CA_OBJS)

all: $(CA_LIB)

cleanall:
	cd $(LIB_DIR); rm $(CA_LIB)