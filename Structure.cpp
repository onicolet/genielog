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
		if (line.compare(strcmp1)==0 || found){
			if (! found){
				found = true;
			}
			else if (found && !line.empty()){
				reference.push_back(line);	
			}
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
	 out << "	</biblio>" << endl;

	 out.close();
}



// --------- VERIFICATION DE CONTENU ---------
bool catchSection(string currentLine, vector<string> cmp) {
cout << "80" << endl;	
// Si détection d'une chaîne définie dans le dictionnaire cmp on retourne VRAI
	for (unsigned int index=0; index < cmp.size(); index++)
		if (cmp[index].compare(currentLine)==0)
			return true;
	
cout << "86" << endl;	
	// Sinon on retourne FAUX
	return false;
}



// --------- INTRODUCTION ---------
void Structure::getCorpsViaScript(string fichierResultat, string fileName, int nbLigneConclusion) {
	// Déclaration
	ifstream file;
	bool sectionFound;
	int n = 0;

	// Booleans
	bool corps = false;
	bool introduction= false;
	bool conclusion= false;
	bool incrementationIndex = false;

	int index; // Compteur indicant la fin de l'introduction
	string currentLine;
	vector<string> introductionVec, corpsVec, conclusionVec, stringToCompareWithIntro,stringToCompareWithRef;

	// Initialisation
	index=0;
	file.open(fichierResultat);

	// Dictionnaire de comparaison (references)
	stringToCompareWithRef.push_back("References");

	// Dictionnaire de comparaison (introduction)
	stringToCompareWithIntro.push_back("1 INTRODUCTION");
	stringToCompareWithIntro.push_back("1 Introduction");
	stringToCompareWithIntro.push_back("1. Introduction");
	stringToCompareWithIntro.push_back("1. INTRODUCTION"); 
	stringToCompareWithIntro.push_back("I Introduction");
	stringToCompareWithIntro.push_back("I INTRODUCTION");
	stringToCompareWithIntro.push_back("I. Introduction");
	stringToCompareWithIntro.push_back("I. INTRODUCTION");
	
	while (!file.eof()) {
		getline(file, currentLine);
		n++;
		incrementationIndex = false;
	 
		if (catchSection(currentLine, stringToCompareWithIntro) || introduction) {
			introduction = true;

			/* Si on détecte un point en fin de ligne, on incrémente
			 * l'index
			 * */
			if (!currentLine.empty() && currentLine.substr(currentLine.size() - 1, 1) == ".")
			{
				index++;
				incrementationIndex = true;
			}
			// Si la ligne courante est vide et que l'index est > 0
			if (index > 0 && currentLine.empty())
			{
				index++;
				incrementationIndex = true;
			}

			/* Si l'index est supérieur ou égal à 2 et que les premiers 
			 * caractères de la ligne courante commencent par "2 ", "2.",
			 * "II " ou encore  "II." alors l'introduction est considérée
			 * comme terminée 
		 	 * */
			if (index >= 2 && !currentLine.empty() 
				&& (currentLine.substr(0,2)=="2." 
					|| currentLine.substr(0,2)=="2 " 
					|| currentLine.substr(0,3)=="II."
					|| currentLine.substr(0,3)=="II "))
			{
				introduction = false;
				corps = true;
			}
			else  // Sinon on réinitialise le compteur à zéro
			{
				introductionVec.push_back(currentLine);
				if(!incrementationIndex)
					index = 0;
			}
		}
		if(n == nbLigneConclusion || conclusion)
		{
			if(conclusion == false)
			{
				corps = false;
				conclusion = true;
			}
			if(catchSection(currentLine, stringToCompareWithRef))
			{
				break;
			}
			else
			{
				conclusionVec.push_back(currentLine);
			}
		}
		if(corps)
		{
			corpsVec.push_back(currentLine);
		}
	} // Fin de la boucle alimentant l'introduction

	if (param == 1)
		writeIntroductionInFileX(fileName, introductionVec);
	else
		writeIntroductionInFile(fileName, introductionVec);

	if (param == 1)
		writeBodyInFileX(fileName, corpsVec);
	else
		writeBodyInFile(fileName, corpsVec);

	if (param == 1)
		writeConclusionInFileX(fileName, conclusionVec);
	else
		writeConclusionInFile(fileName, conclusionVec);
}


void Structure::writeIntroductionInFileX(string FileName, vector<string> introduction) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de l'introduction dans le fichier .xml
	out << "\n\t<introduction>" << endl;
	for (unsigned int index=0; index < introduction.size(); index++)
		out << "\t\t" << introduction[index];
	out << "\n\t</introduction>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeIntroductionInFile(string FileName, vector<string> introduction) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de l'introduction dans le fichier .xml
	out << "Introduction:" << endl;
	for (unsigned int index=0; index < introduction.size(); index++)
		out << introduction[index] ;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeBodyInFileX(string FileName, vector<string> body) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de body dans le fichier .xml
	out << "\n\t<body>" << endl;
	for (unsigned int index=0; index < body.size(); index++)
		out << "\t\t" << body[index];
	out << "\n\t</body>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeBodyInFile(string FileName, vector<string> body) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de body dans le fichier .xml
	out << "Body: " << endl;
	for (unsigned int index=0; index < body.size(); index++)
		out << body[index] << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeConclusionInFileX(string FileName, vector<string> conclusion) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de conclusion dans le fichier .xml
	out << "\n\t<conclusion>" << endl;
	for (unsigned int index=0; index < conclusion.size(); index++)
		out << "\t\t" << conclusion[index];
	out << "\n\t</conclusion>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeConclusionInFile(string FileName, vector<string> conclusion) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de conclusion dans le fichier .xml
	out << "conclusion:" << endl;
	for (unsigned int index=0; index < conclusion.size(); index++)
		out << conclusion[index];

	// Fermeture du fichier .xml
	out.close();
}
