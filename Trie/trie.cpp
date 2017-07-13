#include "stdafx.h"
#include "Trie.h"

Node::Node()
{
	count = 0;
	for (size_t i = 0; i < 26; i++)
	{
		children[i] = nullptr;
	}
}

Node::~Node()
{
	for (size_t i = 0; i < 26; i++)
	{
		if (children[i])
		{
			delete children[i];
		}
	}
}

Trie::Trie()
{
	root = new Node;
}

Trie::~Trie()
{
	delete root;
}

void Trie::addWord(const string & word)
{
	addWord(root, word);
}

vector<string> Trie::getSuggestions(const string & beginning)
{
	vector<string> result;

	Node *curr = root;
	size_t i = 0, length = beginning.length();
	while (curr && i < length)
	{
		curr = curr->children[beginning[i] - 'a'];
		i++;
	}
	if (curr)
	{
		getSuggestions(curr, result, beginning.substr(0));
	}

	return result;
}

bool Trie::find(const string & word)
{
	Node *curr = root;
	size_t i = 0, length = word.length();
	while (curr && i < length)
	{
		curr = curr->children[word[i] - 'a'];
		i++;
	}
	return curr && curr->count;
}

bool Trie::remove(const string & word)
{
	Node *curr = root;
	size_t i = 0, length = word.length();
	while (curr && i < length)
	{
		curr = curr->children[word[i] - 'a'];
		i++;
	}
	if (curr && curr->count)
	{
		curr->count--;
		return true;
	}
	return false;
}

int Trie::getValue(const string & word)
{
	Node *curr = root;
	size_t i = 0, length = word.length();
	while (curr && i < length)
	{
		curr = curr->children[word[i] - 'a'];
		i++;
	}
	return curr ? curr->count : 0;
}

void Trie::addWord(Node *& node, const string & word)
{
	if (word.empty())
	{
		(node->count)++;
	}
	else
	{
		Node *& target = node->children[word[0] - 'a'];
		if (!target)
		{
			target = new Node;
		}
		addWord(target, word.substr(1));
	}
}

void Trie::getSuggestions(Node * node, vector<string>& result, string& curr)
{
	if (node->count)
	{
		result.push_back(curr);
	}
	for (size_t i = 0; i < 26; i++)
	{
		if (node->children[i])
		{
			curr.push_back(i + 'a');
			getSuggestions(node->children[i], result, curr);
			curr.pop_back();
		}
	}
}
