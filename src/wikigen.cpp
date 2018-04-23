#include <iostream>
#include <string>
#include "../lib/pugixml/pugixml.hpp"
#include "../inc/wikigen.hpp"

void print(std::string str)
{
	std::cout << str << std::endl;
}

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(TEST_FILENAME);

	
	for(pugi::xml_node page: doc.child("mediawiki").children("page")) { 
        std::string text = page.child("revision").child_value("text");
        print(text);
    }

    return 0;
}