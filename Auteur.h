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
	int param;
public:
	void getAbstractViaScript(string fichierResultat,string);
	void getAuteurViaScript(string fichierResultat,string);
	void writeFileAbstract(string FileName, vector<string> abstract);
	void writeFileAbstractX(string, vector<string>);
	void writeFileAuteur(string FileName, vector<string> abstract);
	void writeFileAuteurX(string, vector<string>);

	Auteur();
	Auteur(string);
	~Auteur();
};

