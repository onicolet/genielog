#pragma once
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Titre
{
private:
	int param;
public:
	Titre();
	Titre(string);
	~Titre();
	void getTitreViaScript(string fichierResultat,string);
	void writeFile(string FileName, vector<string> titre);
	void writeFileX(string, vector<string>);

};

