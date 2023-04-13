# select all .ice files in the directory and generate the cpp and h files
ICEFILE = $(wildcard *.ice)

gen : 
	slice2cpp $(ICEFILE)

clean :
	rm *.cpp *.h