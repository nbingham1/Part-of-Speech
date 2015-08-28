/*
 * syntax.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: nbingham
 */

#include "syntax.h"
#include <math.h>

markov::markov()
{
	size = 0;
}

markov::~markov()
{

}

void markov::add_str(string s)
{
	vector<string> split;

	string temp;
	string::iterator i;
	int j = 0;

	temp = "";
	char last = ' ';
	for (i = s.begin(); i != s.end(); i++)
	{
		if (*i == ' ')
		{
			if (temp != "")
				split.push_back(temp);
			temp = "";
		}
		else if (*i == ',' || *i == '.' || *i == '!' || *i == '?' || *i == ';' || *i == ':' || *i == '\"')
		{
			if (temp != "")
				split.push_back(temp);
			temp = "";
			temp += *i;
		}
		else
			temp += tolower(*i);
		last = *i;
	}

	map<string, int>::iterator from, to;
	to = words.find(".");
	if (to == words.end())
		to = words.insert(pair<string, int>(".", size++)).first;
	for (j = 0; j < split.size(); j++)
	{
		from = to;
		to = words.find(split[j]);
		if (to == words.end())
			to = words.insert(pair<string, int>(split[j], size++)).first;

		if (in_total.size() < size)
			in_total.resize(size+100, 0.0);
		if (out_total.size() < size)
			out_total.resize(size+100, 0.0);
		if (input.size() < size)
			input.resize(size+100, vector<float>());
		if (output.size() < size)
			output.resize(size+100, vector<float>());

		in_total[to->second]++;
		out_total[from->second]++;
		if (output[from->second].size() < size)
			output[from->second].resize(size+100, 0.0);
		output[from->second][to->second]++;
		if (input[to->second].size() < size)
			input[to->second].resize(size+100, 0.0);
		input[to->second][from->second]++;
	}
}

void markov::add_file(string f)
{
	FILE *file = fopen(f.c_str(), "r");


	char c = 'a';
	string temp;

	while (!feof(file))
	{
		c = fgetc(file);
		while (c != '.' && !feof(file))
		{
			if (c != '\n' && c != '\r')
				temp += c;
			else
				temp += ' ';
			c = fgetc(file);
		}

		if (c == '.')
			temp += c;

		add_str(temp);
		temp = "";
	}

	cout << "done" << endl;

	fclose(file);
}

void markov::print_in()
{
	map<string, int>::iterator i, j;
	for (i = words.begin(); i != words.end(); i++)
	{
		cout << i->first << endl;
		for (j = words.begin(); j != words.end(); j++)
			if (j->second < input[i->second].size() && input[i->second][j->second] > 0)
				cout << "\t" << input[i->second][j->second]/in_total[i->second] << "\t" << j->first << endl;
	}
}

void markov::print_out()
{
	map<string, int>::iterator i, j;
	for (i = words.begin(); i != words.end(); i++)
	{
		cout << i->first << endl;
		for (j = words.begin(); j != words.end(); j++)
			if (j->second < output[i->second].size() && output[i->second][j->second] > 0)
				cout << "\t" << output[i->second][j->second]/out_total[i->second] << "\t" << j->first << endl;
	}
}

void markov::similar(string word)
{
	map<float, string> sim;

	map<string, int>::iterator j, k;
	int x;
	float a, b;
	k = words.find(word);
	if (k == words.end())
	{
		cout << word << " not found." << endl;
		return;
	}
	float error;
	for (j = words.begin(); j != words.end(); j++)
	{
		error = 0.0;
		for (x = 0; x < output[j->second].size() || x < input[j->second].size() || x < output[k->second].size() || x < input[k->second].size(); x++)
		{
			if (x < output[j->second].size())
				a = output[j->second][x]/out_total[j->second];
			else
				a = 0.0;

			if (x < output[k->second].size())
				b = output[k->second][x]/out_total[k->second];
			else
				b = 0.0;

			error += (b - a)*(b - a);

			if (x < input[j->second].size())
				a = input[j->second][x]/in_total[j->second];
			else
				a = 0.0;

			if (x < input[k->second].size())
				b = input[k->second][x]/in_total[k->second];
			else
				b = 0.0;

			error += (b - a)*(b - a);
		}

		sim.insert(pair<float, string>(error, j->first));
	}

	map<float, string>::iterator i;
	for (i = sim.begin(); i != sim.end(); i++)
		cout << i->first << "\t" << i->second << endl;
}
