#pragma once
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class Auteur {
private:
	int param;
public:

	void getAuteurViaScript(string fichierResultat,string);
	void writeFileAuteur(string FileName, vector<string> abstract);
	void writeFileAuteurX(string, vector<string>);

	Auteur();
	Auteur(string);
	~Auteur();
};

