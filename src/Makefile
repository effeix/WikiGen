CC = g++
CFLAGS = -Wall -pedantic --std=c++11

all: pugixml.o tokenizer.o node.o trie.o
	$(CC) $(CFLAGS) -o wikigen main.cpp $^

node.o: ../inc/Node.hpp Node.cpp
	$(CC) $(CFLAGS) -o node.o -c Node.cpp

trie.o: ../inc/Trie.hpp ../inc/NGram.hpp ../inc/Node.hpp Trie.cpp
	$(CC) $(CFLAGS) -o trie.o -c Trie.cpp

tokenizer.o: ../inc/tokenizer.hpp ../lib/pugixml-1.9/pugixml.hpp ../lib/pugixml-1.9/pugiconfig.hpp
	$(CC) $(CFLAGS) -o tokenizer.o -c tokenizer.cpp

pugixml.o: ../lib/pugixml-1.9/pugixml.hpp ../lib/pugixml-1.9/pugiconfig.hpp
	$(CC) $(CFLAGS) -o pugixml.o -c ../lib/pugixml-1.9/pugixml.cpp 