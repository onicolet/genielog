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
public:
	Titre();
	~Titre();
	void getTitreViaScript(string fichierResultat,string);
	void writeFile(string FileName, string titre);
};

