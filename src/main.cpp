#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "ngram.hpp"
#include "tokenizer.hpp"
#include "trie.hpp"
#include "main.hpp"


// Based on: https://github.com/errollw/gengram/blob/master/gengram.py
std::vector<std::vector<std::string>> make_ngrams(std::vector<std::string>& corpus, unsigned int n) {
	
	std::vector<std::vector<std::string>> ngrams;
	
	for(unsigned int i = 0; i < corpus.size() - n + 1; i++) {
		std::vector<std::string> words;

		words.insert(words.end(), corpus.begin()+i, corpus.begin()+i+n);
		
		ngrams.push_back(words);
	}

	return ngrams;
}

ngram_frequency_map make_nfm(std::vector<std::vector<std::string>> ngrams) {

	ngram_frequency_map nfm;

	for(std::vector<std::string> ngram: ngrams) {
		if(nfm.count(ngram) == 0)
			nfm[ngram] = 1;
		else
			nfm[ngram] += 1;
	}

	return nfm;
}

void print_ngrams(std::vector<std::vector<std::string>>& ngrams) {
	for(std::vector<std::string> ngram: ngrams) {
		std::copy(ngram.begin(), ngram.end(), std::ostream_iterator<std::string>(std::cout, " "));
		std::cout << std:: endl;
	}
}

void print_ngrams_map(ngram_frequency_map nfm) {
	std::cout << "NGRAMS" << std::endl;

	for(auto it = nfm.begin(); it != nfm.end(); ++it) {
		std::copy(it->first.begin(), it->first.end(), std::ostream_iterator<std::string>(std::cout, " "));
		std::cout << ": " << it->second;
		std::cout << std::endl;
	}
}

int main(int argc, char const *argv[]) {

	std::string filename = CUSTOM_FILE;	
	std::vector<std::string> tokenized_corpus = read_xml(filename);

	ngrams ngrams = make_ngrams(tokenized_corpus, std::stoi(argv[1]));

	ngram_frequency_map nfm = make_nfm(ngrams);

	print_ngrams_map(nfm);

	Trie * trie = new Trie();
	trie->build_trie(nfm);
	trie->print_trie(trie->root->get_children()["wb"]);

    return 0;
}