#include "node.hpp"

std::string Node::get_value() {
	return this->value;
}

void Node::set_value(std::string _value) {
	this->value.assign(_value);
}

std::map<std::string, Node*> Node::get_children() {
	return this->children;
}

void Node::set_child(std::string word, Node* node) {
	this->children[word] = node;
}

int Node::get_count() {
	return this->count;
}

void Node::set_count(int _count) {
	this->count = count;
}