#ifndef __WIKIGEN_NODE_H__
#define __WIKIGEN_NODE_H__

#include <map>
#include <string>

class Node {
private:
	std::string value;
	std::map<std::string, Node*> children;
	int count;
public:
	Node(std::string value);

	std::string get_value();
	void set_value(std::string value);

	std::map<std::string, Node*> get_children();
	void add_child(Node * node);

	void set_count(int count);
	int get_count();

	int level;
};

#endif/*__WIKIGEN_NODE_H__*/