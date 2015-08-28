/*
 * main.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: nbingham
 */

#include "syntax.h"

int main()
{
	markov m;

	m.add_file("book");

	//m.print_out();
	m.similar("the");
}



