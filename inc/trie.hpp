#ifndef __WIKIGEN_TRIE_H__
#define __WIKIGEN_TRIE_H__

#include "ngram.hpp"
#include "node.hpp"

class Trie {
private:
	std::vector<Node *> trie;
public:
	Trie();
	~Trie();
	void add(Node * node);
    void build_trie(ngram_frequency_map nfm);
    void print_trie(Node * node);
    int count(Node * node);
    Node * root;
};

#endif/*__WIKIGEN_TRIE_H__*/