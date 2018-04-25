#ifndef __WIKIGEN_TOKENIZER_H__
#define __WIKIGEN_TOKENIZER_H__

#include <string>
#include <vector>

#include <boost/tokenizer.hpp>

typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

std::vector<std::string> read_documents_file(std::string& fname);
std::vector<std::string> read_xml(std::string& fname);
std::vector<std::string> tokenize(std::string& content);
void sanitize(std::string& content);
bool is_unwanted_char(char c);

#endif/*__WIKIGEN_TOKENIZER_H__*/