#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

void trim (string &str)
{
	int i = 0;
	int spacesBegin = 0;
	while (' ' == str[i++])
	{
		spacesBegin++;
	}

	i = str.length();
	int spacesEnd = 0;

	while (' ' == str[--i])
	{
		spacesEnd++;
	}

	int strLength;

	strLength = str.length() - spacesBegin - spacesEnd;

	str = str.substr(spacesBegin, strLength);
}

void swap(int &x, int &y) 
{
	int a;
	a = x;
	x = y;
	y = a;
}