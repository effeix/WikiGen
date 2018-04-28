#ifndef __WIKIGEN_NODE_H__
#define __WIKIGEN_NODE_H__

#include <map>
#include <string>

class Node {
private:
	std::string value = "";
	std::map<std::string, Node*> children;
	int count = 0;
public:
	std::string get_value();
	void set_value(std::string _value);
	std::map<std::string, Node*> get_children();
	void set_child(std::string word, Node* node);
	void set_count(int _count);
	int get_count();
};

#endif/*__WIKIGEN_NODE_H__*/