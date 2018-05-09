#include "node.hpp"

Node::Node(std::string value) : value(value) {
	this->set_count(0);
}

std::string Node::get_value() {
	return this->value;
}

void Node::set_value(std::string value) {
	this->value.assign(value);
}

std::map<std::string, Node*> Node::get_children() {
	return this->children;
}

void Node::add_child(Node * node) {
	this->children[node->get_value()] = node;
}

int Node::get_count() {
	return this->count;
}

void Node::set_count(int count) {
	this->count = count;
}