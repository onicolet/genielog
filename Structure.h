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

	void getBiblioViaScript(string, string,int);
	void writeFile(string, vector<string>);
	void writeFileX(string, vector<string>);

	void getCorpsViaScript(string, string, int,int,int,int);
	void getConclusionViaScript(string, string, int, int);
	void getDiscussionViaScript(string, string, int, int, int,int);
	void getIntroductionViaScript(string , string , int , int ,int);


	void writeIntroductionInFile(string, vector<string>);
	void writeIntroductionInFileX(string, vector<string>);

	void writeBodyInFile(string, vector<string>);
	void writeBodyInFileX(string, vector<string>);

	void writeDiscussionInFile(string, vector<string>);
	void writeDiscussionInFileX(string, vector<string>);

	void writeConclusionInFileX(string, vector<string>);
	void writeConclusionInFile(string, vector<string>);
};
