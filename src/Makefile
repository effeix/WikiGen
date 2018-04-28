CC = g++
CFLAGS = -Wall -pedantic --std=c++11
LIB_DIR = ../lib
LIBS = pugixml
INC_DIR = ../inc
INC_FLAG = -I$(INC_DIR) $(foreach lib, $(LIBS), -I$(LIB_DIR)/$(lib))
EXEC = wikigen

all: pugixml.o tokenizer.o node.o trie.o main.o
	$(CC) $(CFLAGS) $^ -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

pugixml.o: $(LIB_DIR)/pugixml/pugixml.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(EXEC)

# print-%: ; @echo $* = $($*)