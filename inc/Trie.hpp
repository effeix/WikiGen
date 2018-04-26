#include "NGram.hpp"
#include "Node.hpp"

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

    // void print_tree(map<char, Node*> tree);
    // void print();
};