#ifndef __WIKIGEN_TRIE_H__
#define __WIKIGEN_TRIE_H__

#include "ngram.hpp"
#include "node.hpp"

class Trie {
protected:
    Node* root;
    std::vector<Node*> children;
public:
    void build_trie(ngram_freq_table table);
    void insert(ngram ngram);
    void search(ngram, bool &result);
    void print_trie(Node* node);
    Node* get_root();
};

#endif/*__WIKIGEN_TRIE_H__*/