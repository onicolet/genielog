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
	int startBody=0;
	int endBody=0;
public:
	Structure();
	Structure(string);
	~Structure();

	void getBiblioViaScript(string, string);
	void writeFile(string, vector<string>);
	void writeFileX(string, vector<string>);

	void getIntroductionViaScript(string, string);
	void writeIntroductionInFile(string, vector<string>);
	void writeIntroductionInFileX(string, vector<string>);

	void getBodyViaScript(string, string);
	void writeBodyInFile(string, vector<string>);
	void writeBodyInFileX(string, vector<string>);

	void getConclusionViaScript(string, string);
	void writeConclusionInFileX(string, vector<string>);
	void writeConclusionInFile(string, vector<string>);
};
