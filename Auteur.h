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
	void getAbstractViaScript(string,string);
	void getAuteurViaScript(string ,string,int);
	void writeFileAbstract(string, vector<string> );
	void writeFileAbstractX(string, vector<string>);
	void writeFileAuteur(string , vector<string>);
	void writeFileAuteurX(string, vector<string>);
	bool catchSection2(string , vector<string>) ;
	Auteur();
	Auteur(string);
	~Auteur();
};

