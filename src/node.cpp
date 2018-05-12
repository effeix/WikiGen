#include "node.hpp"

Node::Node(std::string _value) {
	this->value = _value;
	this->set_count(0);
}

std::string Node::get_value() {
	return this->value;
}

void Node::set_value(std::string value) {
	this->value = value;
}

std::map<std::string, Node*> Node::get_children() {
	return this->children;
}

void Node::add_child(Node * node) {
	this->children[node->get_value()] = node;
}

bool Node::has_children() {
	return this->children.empty();
}

std::map<std::string, Node*>::iterator Node::begin() {
	return this->children.begin();
}

std::map<std::string, Node*>::iterator Node::end() {
	return this->children.end();
}

int Node::get_count() {
	return this->count;
}

void Node::set_count(int count) {
	this->count = count;
}