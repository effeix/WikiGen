#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"
#include "trie.hpp"

Trie::Trie() {}

Trie::~Trie() {
	for(unsigned int i = 0; i < this->trie.size(); i++) {
    	//delete this->trie[i];
  	}
}

void Trie::add(Node * node) {
	this->trie.push_back(node);
}

void Trie::build_trie(ngram_frequency_map nfm) {
	/*
		nfm = {
			["you", "are", "the", "best"]: 2,
			["you", "are", "the", "worst"]: 1
		}
	*/

	this->root = new Node("$");
	Node * current_node;
	
	std::string current_word;

	for(auto it = nfm.begin(); it != nfm.end(); ++it) {
		
		current_node = this->root;

		for(unsigned int i = 0; i < it->first.size(); i++) {
			current_word = it->first[i];
			Node * node;

			if(current_node->get_children().count(current_word) == 0) {
				node = new Node(current_word);
				current_node->add_child(node);
			}
			else {
				node = current_node->get_children()[current_word];
			}

			current_node = node;

			if(i == it->first.size() - 1) {
				current_node->set_count(it->second);
			}
		}
	}

	this->count(this->root);
}

int Trie::count(Node * node) {
	if(node->get_children().size() != 0) {
		int count = 0;

		for(auto it = node->begin(); it != node->end(); ++it) {
			count += this->count(it->second);
		}

		node->set_count(count);
	}

	return node->get_count();
}

void Trie::print_trie(Node * node) {
	std::cout << "Node: " << node->get_value() << " - " << node->get_count() << std::endl;
	for(std::map<std::string, Node*>::iterator it = node->begin(); it != node->end(); ++it) {
		this->print_trie(it->second);
	}
}