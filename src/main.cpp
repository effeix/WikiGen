#include <iostream>
#include <string>

#include "../inc/tokenizer.hpp"
#include "../inc/main.hpp"


// Based on: https://github.com/errollw/gengram/blob/master/gengram.py
std::vector<std::vector<std::string>> make_ngrams_2(std::vector<std::string>& corpus, unsigned int n) {
	
	std::vector<std::vector<std::string>> ngrams;
	
	for(unsigned int i = 0; i < corpus.size() - n + 1; i++) {
		std::vector<std::string> words;

		words.insert(words.end(), corpus.begin()+i, corpus.begin()+i+n);
		
		ngrams.push_back(words);
	}

	return ngrams; // if n == 3: [[w0,w1,w2], [w1,w2,w3], ...]
}

void print_ngrams(std::vector<std::vector<std::string>>& ngrams) {
	for(std::vector<std::string> ngram: ngrams) {
		int idx = -1;
		std::cout << "[";
		for(std::string word: ngram) {
			idx++;
			if(idx == (int)ngram.size()-1) {
				std::cout << word;
			}
			else
				std::cout << word << " | ";
		}
		std::cout << "]" << std::endl;
	}
}

int main(int argc, char const *argv[]) {

	std::string filename = ULTRA_TINY_FILE;	
	std::vector<std::string> mini_corpus = read_xml(filename);

	unsigned int ngram_n = N;
	std::vector<std::vector<std::string>> ngrams = make_ngrams_2(mini_corpus, ngram_n);

	print_ngrams(ngrams);

    return 0;
}