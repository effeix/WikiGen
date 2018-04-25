#include <iostream>
#include <string>
#include <map>

#include "../inc/tokenizer.hpp"
#include "../inc/main.hpp"


// Based on: https://github.com/errollw/gengram/blob/master/gengram.py
std::vector<std::vector<std::string>> make_ngrams(std::vector<std::string>& corpus, unsigned int n) {
	
	std::vector<std::vector<std::string>> ngrams;
	
	for(unsigned int i = 0; i < corpus.size() - n + 1; i++) {
		std::vector<std::string> words;

		words.insert(words.end(), corpus.begin()+i, corpus.begin()+i+n);
		
		ngrams.push_back(words);
	}

	return ngrams; // if n == 3: [[w0,w1,w2], [w1,w2,w3], ...]
}

std::map<std::vector<std::string>, std::map<std::string, int>> ngrams_abs_frequency(
	std::vector<std::vector<std::string>> ngrams) {

	/**
	 * For N = 4, this map has the form {"w1,w2,w3,w4": n}
	 * where w4 is the next word with count n
	 */

	std::map<std::vector<std::string>, std::map<std::string, int>> frequencies;

	for(std::vector<std::string> ngram: ngrams) {

		// ngram except for the last word
		std::vector<std::string> ngram_key(ngram.begin(), ngram.end()-1);

		std::string ngram_last_word = ngram.back();

		/**
         * By: Gustavo Efeiche
         *
		 * I could use map.find() or map.count()
		 * but map.find() returns an iterator object,
		 * which we are not going to use.
		 * map.count() returns 1 (exists) or 0 (~exists).
		*/

		// If ngram_key is not map key
		if(frequencies.count(ngram_key) == 0) {
			std::map<std::string, int> next_word_counts;
			next_word_counts[ngram_last_word] = 1;
			frequencies[ngram_key] = next_word_counts;
		}
		else {
			// If last word is key of next_word_counts map
			if(frequencies[ngram_key].count(ngram_last_word) == 0) {
				frequencies[ngram_key][ngram_last_word] = 1;
			}
			else {
				frequencies[ngram_key][ngram_last_word] += 1;
			}
		}
	}

	return frequencies;
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

void print_ngrams_map(std::map<std::vector<std::string>, std::map<std::string, int>>& ngrams_map) {
	for(auto it = ngrams_map.cbegin(); it != ngrams_map.end(); ++it) {
		std::cout << "{(";
		for(unsigned int i = 0; i < it->first.size(); i++) {
			std::cout << it->first[i];
			if(i != it->first.size()-1) {
				std::cout << " | ";	
			}
			else {
				std::cout << "): ";
			}
		}

		std::cout << "{";
		for(auto itt = it->second.cbegin(); itt != it->second.cend(); ++itt) {
			std::cout << "'" << itt->first << "': " << itt->second;
			if(std::next(itt) != it->second.cend())
				std::cout << ", ";
		}
		std::cout << "}";

		std::cout << "}" << std::endl;
		// std::cout << it->first[0] << std::endl;
	}
}

int main(int argc, char const *argv[]) {

	std::string filename = TINY_FILE;	
	std::vector<std::string> mini_corpus = read_xml(filename);

	unsigned int ngram_n = N;
	std::vector<std::vector<std::string>> ngrams = make_ngrams(mini_corpus, ngram_n);

	print_ngrams(ngrams);

	std::map<std::vector<std::string>, std::map<std::string, int>> abs_frequency = ngrams_abs_frequency(ngrams);

	print_ngrams_map(abs_frequency);

    return 0;
}