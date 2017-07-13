#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>
using namespace std;

struct Node
{
	size_t count;
	Node *children[26];
	Node();
	~Node();
};

class Trie
{
public:
	Trie();
	~Trie();

	void addWord(const string&);
	vector<string> getSuggestions(const string&);
	bool find(const string&);
	bool remove(const string&);
	int getValue(const string&);

private:
	Node *root;

	void addWord(Node *&, const string&);
	void getSuggestions(Node *, vector<string>&, string&);
};

#endif
