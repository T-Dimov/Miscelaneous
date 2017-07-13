// Trie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Trie.h"
#include <iostream>
#include <utility>
using namespace std;

int main()
{
	Trie text;
	string input;
	getline(cin, input);

	size_t length = input.length();
	char *cstring = new char[length + 1];
	strcpy_s(cstring, length + 1, input.c_str());

	char *nextToken = nullptr;
	char *token = strtok_s(cstring, " ,.!?&-()[]{}:;\"\'\t", &nextToken);
	while (token)
	{
		input = token;
		text.addWord(input);
		token = strtok_s(nullptr, " ,.!?&-()[]{}:;\"\'\t", &nextToken);
	}

	vector<string> textWords = text.getSuggestions("");
	vector<size_t> occurences;
	length = textWords.size();
	for (size_t i = 0; i < length; i++)
	{
		occurences.push_back(text.getValue(textWords[i]));
	}

	size_t iMax;
	for (size_t i = 0; i < length - 1; i++)
	{
		iMax = i;
		for (size_t j = i + 1; j < length; j++)
		{
			if (occurences[j] > occurences[iMax])
			{
				iMax = j;
			}
		}
		if (iMax != i)
		{
			swap(occurences[i], occurences[iMax]);
			swap(textWords[i], textWords[iMax]);
		}
	}

	cout << "\n10 most common words in the text with respective occurences:\n";
	for (size_t i = 0; i < length && i < 10; i++)
	{
		cout << textWords[i] << '\t' << occurences[i] << endl;
	}

	cin.get();
	delete cstring;
	return 0;
}

