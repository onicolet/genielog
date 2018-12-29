#pragma once
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class Structure {
private:
	int param;
public:
	Structure();
	Structure(string);
	~Structure();
	void getBiblioViaScript(string, string);
	void writeFile(string, vector<string>);
	void writeFileX(string, vector<string>);
};
