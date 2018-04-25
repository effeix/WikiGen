#include <iostream>
#include <string>

#include "../inc/tokenizer.hpp"
#include "../inc/main.hpp"

int main(int argc, char const *argv[]) {

	std::string filename = TINY_FILE;	
	std::vector<std::string> mini_corpus = read_xml(filename);

    return 0;
}