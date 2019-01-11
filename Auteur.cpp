#include "Auteur.h"


Auteur::Auteur(string par) {
	if (par.compare("-x") == 0)
		param = 1;
	else
		param = 2;
}



// --------- VERIFICATION DE CONTENU ---------
bool Auteur::catchSection2(string currentLine, vector<string> cmp) {	
// Si détection d'une chaîne définie dans le dictionnaire cmp on retourne VRAI

	for (unsigned int index=0; index < cmp.size(); index++)
		if (cmp[index].compare(currentLine)==0)
			return true;
		
	// Sinon on retourne FAUX
	return false;
}



void Auteur::getAuteurViaScript(string fichierResultat, string FileName,int AuteurLine) {
	ifstream file;
	vector<string> auteur;
	string line, strcompare, cmp1 = "Abstract", cmp2 = "ABSTRACT";
	file.open(fichierResultat);
	int n = 0;

	while (! file.eof()) {
		getline(file, line);
		n++;
		strcompare = line.substr (0,8);
		if (cmp1.compare(strcompare)==0 || cmp2.compare(strcompare)==0)
			break;

		if(n>=AuteurLine)
			auteur.push_back(line);
	}

	file.close();

	if(param == 1)
		writeFileAuteurX(FileName,auteur);
	else
		writeFileAuteur(FileName,auteur);
}


void Auteur::getAbstractViaScript(string fichierResultat, string FileName) {
	ifstream file;
	bool found=false;
	vector<string> abstractVec,stringToCompareWithIntro;
	string line, strcompare, cmp1 = "Abstract", cmp2 = "ABSTRACT";
	file.open(fichierResultat);

		// Dictionnaire de comparaison (introduction)
	stringToCompareWithIntro.push_back("Introduction");
	stringToCompareWithIntro.push_back("INTRODUCTION");
	stringToCompareWithIntro.push_back("1 INTRODUCTION");
	stringToCompareWithIntro.push_back("1 Introduction");
	stringToCompareWithIntro.push_back("1. Introduction");
	stringToCompareWithIntro.push_back("1. INTRODUCTION"); 
	stringToCompareWithIntro.push_back("I Introduction");
	stringToCompareWithIntro.push_back("I INTRODUCTION");
	stringToCompareWithIntro.push_back("I. Introduction");
	stringToCompareWithIntro.push_back("I. INTRODUCTION");
	
	int i = 0;
	int n = 0;

	while (!file.eof()) {
		getline(file, line);
		strcompare = line.substr(0,8);
		n++;

		if ((cmp1.compare(strcompare)==0 || cmp2.compare(strcompare)==0) || found) {
			found = true;

			if (catchSection2(line,stringToCompareWithIntro)) {
				break; 
			} else if (!line.empty()) { 	
				if (i != 0)
					abstractVec.push_back(line);
				i++;
			}
		}
	}

	file.close();
	
	if(param == 1)
		writeFileAbstractX(FileName, abstractVec);
	else
		writeFileAbstract(FileName, abstractVec);
}


void Auteur::writeFileAbstract(string FileName, vector<string> abstract) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\nAbstract:" << endl;
	 for (unsigned int z = 0; z<abstract.size(); ++z)
		 out <<"\t" << abstract[z] << endl;

	 out.close();
}


void Auteur::writeFileAuteur(string FileName, vector<string> auteur) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\nAuthor:" << endl;
	 for (unsigned int z = 0; z<auteur.size(); ++z)
		 out <<"\t" << auteur[z] << endl;

	 out.close();
}


void Auteur::writeFileAbstractX(string FileName, vector<string> abstract) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\n\t<abstract>" << endl;;
	 for (unsigned int z = 0; z<abstract.size(); ++z)
		 out <<"\t\t" << abstract[z] << endl;
	 out << "\n\t</abstract>" << endl;

	 out.close();
}


void Auteur::writeFileAuteurX(string FileName, vector<string> auteur) {
	std::ofstream out;
	out.open(FileName, std::ios::app);

	out << "\n\t<auteur> " << endl;;
	for (unsigned int z = 0; z<auteur.size(); ++z)
		out <<"\t\t" << auteur[z] << endl;
	out << "\n\t</auteur>" << endl;

	out.close();
}


Auteur::Auteur() {}


Auteur::~Auteur() {}
