SRC = src/homework2.cpp src/binaryTree.cpp
X = $(SRC:.cc=.o)
EXEC = homework2

all: $(EXEC)

$(EXEC): $(X) 
	g++ $(X) -I include -o $@ 

clean:
	rm -rf $(EXEC)