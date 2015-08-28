#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

#ifndef syntax_h
#define syntax_h

struct markov
{
	markov();
	~markov();

	int size;
	map<string, int> words;
	vector<float> in_total;
	vector<float> out_total;
	vector<vector<float> > input;
	vector<vector<float> > output;

	void add_str(string s);
	void add_file(string f);
	void print_in();
	void print_out();
	void similar(string word);
};

#endif
