#ifndef __WIKIGEN_NGRAM_H__
#define __WIKIGEN_NGRAM_H__

#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> ngram;
typedef std::map<std::vector<std::string>, std::map<std::string, int>> ngram_freq_table;

#endif/*__WIKIGEN_NGRAM_H__*/