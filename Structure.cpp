#include "Structure.h"




Structure::Structure() {}


Structure::Structure(string par) {
	if(par.compare("-x") == 0)
		param = 1 ;	
	else
		param = 2;
}


Structure::~Structure() {}



// --------- BIBLIOGRAPHIE ---------
void Structure::getBiblioViaScript(string fichierResultat, string FileName) {
	ifstream file;
	string line, strcmp1 = "References";
	vector<string> reference;
	bool found = false;
	
	file.open(fichierResultat);
	
	while (!file.eof()) {
		getline(file, line);
		if (line.compare(strcmp1)){
			found = true;
			reference.push_back(line);
		}
	}

	file.close();
	
	if(param == 1)
		writeFileX(FileName,reference);
	else
		writeFile(FileName,reference);
}


void Structure::writeFile(string FileName, vector<string> reference) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "Bibliography: " << endl;
	 for (unsigned int z = 0; z<reference.size(); ++z)
		 out << reference[z] << endl;

	 out << endl;
	 out.close();
}


void Structure::writeFileX(string FileName,vector<string> reference) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "	<biblio>" << endl;
	 for (unsigned int z = 0; z < reference.size(); ++z)
		 out << "		" << reference[z] << endl;
	 out << " </biblio>" << endl;

	 out.close();
}



// --------- VERIFICATION DE CONTENU ---------
bool catchSection(string currentLine, vector<string> cmp) {
	// Si détection d'une chaîne définie dans le dictionnaire cmp on retourne VRAI
	for (int index=0; index < cmp.size(); index++)
		if (cmp[index].compare(currentLine)==0)
			return true;
	
	// Sinon on retourne FAUX
	return false;
}



// --------- INTRODUCTION ---------
void Structure::getIntroductionViaScript(string fichierResultat, string fileName) {
	// Déclaration
	ifstream file;
	bool sectionFound;
	int index; // Compteur indicant la fin de l'introduction
	string currentLine;
	vector<string> introduction, stringToCompareWith;

	// Initialisation
	sectionFound=false;
	index=0;
	file.open(fichierResultat);
	// Dictionnaire de comparaison
	stringToCompareWith.push_back("1 INTRODUCTION");
	stringToCompareWith.push_back("1 Introduction");
	stringToCompareWith.push_back("1. Introduction");
	stringToCompareWith.push_back("1. INTRODUCTION"); 
	stringToCompareWith.push_back("I Introduction");
	stringToCompareWith.push_back("I INTRODUCTION");
	stringToCompareWith.push_back("I. Introduction");
	stringToCompareWith.push_back("I. INTRODUCTION");
	
	while (!file.eof()) {
		getline(file, currentLine);
	 
	 	if (catchSection(currentLine, stringToCompareWith) || sectionFound) {
	 		sectionFound = true;

			/* Si on détecte un point en fin de ligne, on incrémente 
			 * l'index 
			 * */
			if (currentLine.substr(currentLine.size()-1, 1) == ".")
				index++;
			// Si la ligne courante est vide et que l'index est > 0
			if (index>0 && currentLine.empty())
				index++;

			/* Si l'index est supérieur ou égal à 2 et que les premiers 
			 * caractères de la ligne courante commencent par "2 ", "2.",
			 * "II " ou encore  "II." alors l'introduction est considérée
			 * comme terminée 
		 	 * */
			if (	index >= 2 
				&& !currentLine.empty() 
				&& (currentLine.substr(0,2)=="2." 
					|| currentLine.substr(0,2)=="2 " 
					|| currentLine.substr(0,3)=="II."
					|| currentLine.substr(0,3)=="II "))
				break;
			else  // Sinon on réinitialise le compteur à zéro
				index = 0;
		}
	} // Fin de la boucle alimentant l'introduction

	if (param == 1)
		writeFileIntroductionX(fileName, introduction);
	else
		writeFileIntroduction(fileName, introduction);
}


void Structure::writeIntroductionInFileX(string FileName, vector<string> introduction) {
	// Déclaration du flux d'écriture
	std::oftsream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de l'introduction dans le fichier .xml
	out << "	<introduction>" << endl;
	for (unsigned int index=0; index < introduction.size(); index++)
		out << "		" << introduction[index] << endl;
	out << "	</introduction>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeIntroductionInFile(string FileName, vector<string> introduction) {
	std::oftsream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de l'introduction dans le fichier .xml
	out << "Introduction:" << endl;
	for (unsigned int index=0; index < introduction.size(); index++)
		out << introduction[index] << endl;

	// Fermeture du fichier .xml
	out.close();
}



// --------- CORPS ---------
void Structure::getBodyViaScript(string outputFile, string inputFile) {

}


void Structure::writeBodyInFileX(string FileName, vector<string> body) {

}


void Structure::writeBodyInFile(string FileName, vector<string> body) {

}


void Structure::getConclusionViaScript(string outputFile, string inputFile) {

}


void Structure::writeConclusionInFileX(string FileName, vector<string> conclusion) {

}


void Structure::writeConclusionInFile(string FileName, vector<string> conclusion) {

}
