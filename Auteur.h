#pragma once
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Auteur
{
private:
	char** nomAuteur;
public:
	string * getAuteurs();
	void getAuteursViaScript(string fichierResultat);
	Auteur();
	~Auteur();
};

