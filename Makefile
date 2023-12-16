# Chem 274B: Software Engineering Fundataions for
#            Molecular Sciences 
# University of California, Berkeley

# This creates executables for tests of sorting functions. 

# SRC directory
SRC_DIR = ./src

#Test Directory
TEST_DIR = ./Tests

# Executable programs
BIN_DIR     = ./Bin

# The next line contains a list of executable object files 
# created by this Makefile.
TEST_EXECUTABLES = CA_test

test:
	cd $(SRC_DIR); make all; cd ..
	cd $(TEST_DIR); make all; cd ..

run:
	cd $(BIN_DIR); ./COVID_test; cd ..
	cd $(BIN_DIR); ./CA_test; cd ..

all: $(TEST_EXECUTABLES)

clean:
	cd $(BIN_DIR); rm -f *.txt