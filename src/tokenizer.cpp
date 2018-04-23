#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#include "../lib/boost_1_67_0/tokenizer.hpp"
#include "../lib/pugixml-1.9/pugixml.hpp"

std::vector<std::string> read_documents_file(std::string fname) {
	std::ifstream infile;
	std::vector<std::string> documents;
	std::string document;

	infile.open(fname);

	while(!infile.eof()) {
		getline(infile, document);
		documents.push_back(document);
	}

	infile.close();

	return documents;
}

std::vector<std::string> readXML(std::string& fname) {
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(fname.c_str());
	pugi::xml_node document_root = document.child("mediawiki");

	std::vector<std::string> documents;

	// for(pugi::xml_node page: document_root.children("page")) {

	// }
}