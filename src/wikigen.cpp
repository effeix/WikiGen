#include <iostream>
#include <string>
#include "../lib/pugixml-1.9/pugixml.hpp"
#include "../inc/tokenizer.hpp"
#include "../inc/wikigen.hpp"

void print(std::string str)
{
	std::cout << str << std::endl;
}

int main(int argc, char const *argv[])
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(TEST_FILENAME);

	
	// for(pugi::xml_node page: doc.child("mediawiki").children("page")) { 
 //        std::string text = page.child("revision").child_value("text");
 //        print(text);
 //    }

	std::vector<std::string> documents = read_documents_file("../txt/documents.txt");

	for(std::string str: documents) {
		print(str);
	}     

    return 0;
}