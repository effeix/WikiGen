#include <iostream>
#include "node.hpp"
#include "trie.hpp"

Node* Trie::get_root() {
	return this->root;
}

void Trie::print_trie(Node* node){
	std::cout << node->get_children().size() << std::endl;
	for (auto it = node->get_children().begin(); it != node->get_children().end(); it++)
	{	
		std::cout << it->second << std::endl;
	}
}

void Trie::build_trie(ngram_freq_table table) {
	Node* root = new Node();
	this->root = root;

	for(auto it = table.begin(); it != table.end(); ++it) {
		Node* current_node = root;
		for(unsigned int i = 0; i < it->first.size(); i++) {
			// if word not in node.children
			std::string cur_word = it->first[i];
			if(current_node->get_children().find(cur_word) == current_node->get_children().end()) {
				// Create new node with word ng[i] and add to child list of current node
				Node* new_node = new Node();
				new_node->set_value(cur_word);
				current_node->set_child(cur_word, new_node);

				current_node = new_node;
			}

			if(i == it->first.size() - 1) {
				for(auto itt = table.at(it->first).begin(); itt != table.at(it->first).end(); ++itt) {
					Node* next_word_node = new Node();
					next_word_node->set_value(itt->first);
					next_word_node->set_count(itt->second);
					current_node->set_child(itt->first, next_word_node);
				}
			}
		}
	}
}