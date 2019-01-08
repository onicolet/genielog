#include "Auteur.h"


Auteur::Auteur(string par) {
	if (par.compare("-x") == 0)
		param = 1;
	else
		param = 2;
}

void Auteur::getAuteurViaScript(string fichierResultat, string FileName) {
	ifstream file;
	vector<string> auteur;
	string line, strcompare, cmp1 = "Abstract", cmp2 = "ABSTRACT";
	file.open(fichierResultat);
	int i = 0;

	while (! file.eof()) {
		getline(file, line);
		strcompare = line.substr (0,8);
		if (cmp1.compare(strcompare)==0 || cmp2.compare(strcompare)==0)
			break;

		if(i!=0)
			auteur.push_back(line);
		i++;
	}

	file.close();

	if(param == 1)
		writeFileAuteurX(FileName,auteur);
	else
		writeFileAuteur(FileName,auteur);
}


void Auteur::writeFileAuteur(string FileName, vector<string> auteur) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "Author: " ;
	 for (unsigned int z = 0; z<auteur.size(); ++z)
		 out << auteur[z];

	 out.close();
}


void Auteur::writeFileAuteurX(string FileName, vector<string> auteur) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "	<auteur> " ;
	 for (unsigned int z = 0; z<auteur.size(); ++z)
		 out << auteur[z];

	 out << " </auteur>" << endl;
	 out.close();
}


Auteur::Auteur() {}


Auteur::~Auteur() {}
