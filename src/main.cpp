#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>

#include "ngram.hpp"
#include "tokenizer.hpp"
#include "trie.hpp"
#include "main.hpp"

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

std::string random_word(std::vector<std::string>& words, std::vector<int>& counts) {
	std::random_device rd;
    std::mt19937 generator(rd());

	std::discrete_distribution<int> distribution(counts.begin(), counts.end());
	int i = distribution(generator);
	return words[i];
}

std::string make_random_text(Node * root, unsigned int nwords, unsigned int ngram_size) {
	Node * current_node;
	std::vector<std::string> final_text_vector;
	std::string new_word = "";
	std::string final_text = "";
	unsigned int level = 0;

	for(unsigned int i = 0; i < nwords; i++) {

		current_node = root;

		if(i != 0) {
			current_node = root->children[final_text_vector.back()];
		}

		while(level < ngram_size) {

			std::vector<std::string> words;
			std::vector<int> counts;

			for(auto it = current_node->begin(); it != current_node->end(); ++it) {
				words.push_back(it->first);
				counts.push_back(it->second->get_count());
			}

			std::string word = random_word(words, counts);
			final_text_vector.push_back(word);

			current_node = current_node->children[word];

			level++;
		}

		level = 1;
	
	}

	for(std::string word: final_text_vector)
		final_text += word + " ";

	return final_text;
}

Node * make_trie(ngram_frequency_map nfm) {
	Trie * trie = new Trie();
	trie->build_trie(nfm);
	return trie->root;
}

int main(int argc, char const *argv[]) {

	unsigned int NGRAM_SIZE = std::stoi(argv[1]);
	unsigned int N_WORDS    = std::stoi(argv[2]);
	std::string XML_FILE;

	if(argc >= 4) {
		XML_FILE = argv[3];
	} else {
		XML_FILE = "../xml/wikidump-tiny.xml";
	}
	
	std::vector<std::string> tokenized_corpus = read_xml(XML_FILE);

	ngrams ngrams           = make_ngrams(tokenized_corpus, NGRAM_SIZE);
	ngram_frequency_map nfm = make_nfm(ngrams);
	Node * trie             = make_trie(nfm);

	std::cout << make_random_text(trie, N_WORDS, NGRAM_SIZE) << std::endl;

    return 0;
    
}