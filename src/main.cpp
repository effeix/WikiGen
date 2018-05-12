#include <boost/mpi.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>

#include "ngram.hpp"
#include "tokenizer.hpp"
#include "trie.hpp"
#include "main.hpp"

namespace mpi = boost::mpi;
unsigned int MASTER = 0;
unsigned int TAG0 = 0;
unsigned int TAG1 = 1;
unsigned int TAG2 = 2;

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

std::string make_random_text(Node * root, unsigned int nwords, unsigned int ngram_size, mpi::communicator comm) {
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

			std::string word;

			/*
				In each node, create a vector with words and a vector with counts.
				These vectors are then going to be sent to the master node, joined,
				and counts vector will be used to select a value based on weights
				(the counts). Finally, words will be used to select a word based on
				that count.
			*/
			std::vector<std::string> words;
			std::vector<int> counts;

			for(auto it = current_node->begin(); it != current_node->end(); ++it) {
				words.push_back(it->first);
				counts.push_back(it->second->get_count());
			}

			// If I'm inside a worker node, send the vectors to master
			// Lastly, receive last selected word to start new traversal
			if(comm.rank() > 0) {
				comm.send(MASTER, TAG0, words);
				comm.send(MASTER, TAG1, counts);
				comm.recv(MASTER, TAG2, word);
			}
			// If I'm inside master node, join all received vectors and select a random word
			else {
				unsigned rank;
				// Join vectors, exclude master node
				for(rank = 1; rank < comm.size(); rank++) {
					std::vector<std::string> recv_words;
					std::vector<int> recv_counts;

					comm.recv(rank, TAG0, recv_words);
					comm.recv(rank, TAG1, recv_counts);

					words.insert(words.end(), recv_words.begin(), recv_words.end());
					counts.insert(counts.end(), recv_counts.begin(), recv_counts.end());
				}

				// Select word
				word = random_word(words, counts);

				// Send selected word to all workers so they all traverse same ngram in the next iteration
				for(rank = 1; rank < comm.size(); rank++) { 
                    comm.send(rank, TAG2, word);
                }      
			}

			// Add selected word to text
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

	mpi::environment env;
	mpi::communicator comm;
	
	std::vector<std::string> tokenized_corpus = read_xml(XML_FILE);

	ngrams ngrams           = make_ngrams(tokenized_corpus, NGRAM_SIZE);
	ngram_frequency_map nfm = make_nfm(ngrams);
	Node * trie             = make_trie(nfm);
	std::string random_text = make_random_text(trie, N_WORDS, NGRAM_SIZE, comm);

	if(comm.rank() == 0) {
		std::cout << random_text << std::endl;
	}

    return 0;
    
}