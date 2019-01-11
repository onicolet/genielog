#include "Structure.h"




Structure::Structure() {}


Structure::Structure(string par) {
	if(par.compare("-x") == 0)
		param = 1 ;	
	else
		param = 2;
}


Structure::~Structure() {}



// --------- VERIFICATION DE CONTENU ---------
bool catchSection(string currentLine, vector<string> cmp) {	
// Si détection d'une chaîne définie dans le dictionnaire cmp on retourne VRAI

	for (unsigned int index=0; index < cmp.size(); index++)
		if (cmp[index].compare(currentLine)==0)
			return true;
		
	// Sinon on retourne FAUX
	return false;
}






// --------- BIBLIOGRAPHIE ---------
void Structure::getBiblioViaScript(string fichierResultat, string FileName,int ligneActuel) {
	ifstream file;
	vector<string> reference, dicRef;
	string line;
	int n = 0;
	int n2 = 0;
	bool found = false;

	dicRef.push_back("References");
	dicRef.push_back("REFERENCES");
	
	file.open(fichierResultat);
	while (!file.eof()) {
		getline(file, line);
		n++;
		if (n >= ligneActuel+1 || found || catchSection(line, dicRef)) {
			found = true;
			n2++;

			if (n2 > 1)
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

	out << "\n\nBibliography:" << endl;
	for (unsigned int z = 0; z<reference.size(); ++z)
		out << "\t" << reference[z] << endl;
	out << endl;

	out.close();
}


void Structure::writeFileX(string FileName,vector<string> reference) {
	std::ofstream out;
	out.open(FileName, std::ios::app);

	out <<	"\t<biblio>" << endl;
	for (unsigned int z = 0; z < reference.size(); ++z)
		out << "\t\t" << reference[z] << endl;
	out << "\n\t</biblio>" << endl;

	out.close();
}



// --------- INTRODUCTION ---------
void Structure::getIntroductionViaScript(string fichierResultat, string fileName, int nbLigneConclusion,int nbLigneDiscussion, int nbLigneReference) {
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
	vector<string> introductionVec, stringToCompareWithIntro;

	// Initialisation
	index=0;
	int n2=0;

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

	file.open(fichierResultat);
	while (!file.eof()) {
		getline(file, currentLine);
		n++;
		incrementationIndex = false;
	 
		if (catchSection(currentLine, stringToCompareWithIntro) || introduction) {
			introduction = true;
			n2++;

			/* Si on détecte un point en fin de ligne, on incrémente
			 * l'index
			 * */
			if (!currentLine.empty() && currentLine.substr(currentLine.size() - 1, 1) == ".") {
				index++;
				incrementationIndex = true;
			}
			// Si la ligne courante est vide et que l'index est > 0
			if (index > 0 && currentLine.empty()) {
				index++;
				incrementationIndex = true;
			}

			/* Si l'index est supérieur ou égal à 2 et que les premiers 
			 * caractères de la ligne courante commencent par "2 ", "2.",
			 * "II " ou encore  "II." alors l'introduction est considérée
			 * comme terminée 
		 	 * */
			if (!currentLine.empty() 
			&& (currentLine.substr(0,2)=="2." 
				|| currentLine.substr(0,2)=="2 " 
				|| currentLine.substr(0,3)=="II."
				|| currentLine.substr(0,3)=="II ")) /*|| n == nbLigneCorps)*/
			{
				break;
			} else if (n2 > 1) {  // Sinon on réinitialise le compteur à zéro
				introductionVec.push_back(currentLine);

				if(!incrementationIndex)
					index = 0;
			}
		}
	} // Fin de la boucle alimentant l'introduction
	file.close();

	if (param == 1)
		writeIntroductionInFileX(fileName, introductionVec);
	else
		writeIntroductionInFile(fileName, introductionVec);

	getCorpsViaScript(fichierResultat, fileName, n,nbLigneConclusion, nbLigneDiscussion,nbLigneReference);

}


void Structure::getCorpsViaScript(string fichierResultat, string fileName, int nbLigneActuel, int nbLigneConclusion, int nbLigneDiscussion, int nbLigneReference) {
	// Déclaration
	ifstream file;
	bool inside = false;
	int n = 0;
	string currentLine;

	vector<string> corpsVec, stringToCompareWithConclusion,stringToCompareWithDiscussion;

	// Dictionnaire de comparaison (conclusion)
	stringToCompareWithDiscussion.push_back("7. Discussion"); // temporaire

	// Dictionnaire de comparaison (conclusion)
	stringToCompareWithConclusion.push_back("Conclusion");
	stringToCompareWithConclusion.push_back("Conclusions");
	stringToCompareWithConclusion.push_back("conclusion");
	stringToCompareWithConclusion.push_back("conclusions");
	stringToCompareWithConclusion.push_back("CONCLUSION");
	stringToCompareWithConclusion.push_back("CONCLUSIONS");

	file.open(fichierResultat);

	while (!file.eof()) {
		getline(file, currentLine);
		n++;

		if (n == nbLigneActuel || inside) {
			inside = true;

			if (nbLigneDiscussion != -1) {
				if (n == nbLigneDiscussion) {
					inside = false;
					break;
				} else {
					corpsVec.push_back(currentLine);
				}
			} else {
				if (catchSection(currentLine, stringToCompareWithConclusion) || n == nbLigneConclusion) {
					inside = false;
					break;
				} else {
					corpsVec.push_back(currentLine);
				}
			}
		}
	}
	file.close();

	if (param == 1)
		writeBodyInFileX(fileName, corpsVec);
	else
		writeBodyInFile(fileName, corpsVec);
	
	getDiscussionViaScript(fichierResultat, fileName, n, nbLigneConclusion,nbLigneDiscussion,nbLigneReference);
}


void Structure::getDiscussionViaScript(string fichierResultat, string fileName, int nbLigneActuel, int nbLigneConclusion,int nbLigneDiscussion,int nbLigneReference) {
	// Déclaration
	ifstream file;
	int n = 0;
	bool inside = false;
	string currentLine;
	int n2=0;

	vector<string> discussionVec, stringToCompareWithConclusion;

	file.open(fichierResultat);
	if (nbLigneDiscussion != -1) {
		// Dictionnaire de comparaison (conclusion)
		stringToCompareWithConclusion.push_back("Conclusion");
		stringToCompareWithConclusion.push_back("Conclusions");
		stringToCompareWithConclusion.push_back("conclusion");
		stringToCompareWithConclusion.push_back("conclusions");
		stringToCompareWithConclusion.push_back("CONCLUSION");
		stringToCompareWithConclusion.push_back("CONCLUSIONS");

		while (!file.eof()) {
			getline(file, currentLine);
			n++;

			if (n == nbLigneActuel || inside) {
				n2++;
				inside = true;
				if (catchSection(currentLine, stringToCompareWithConclusion) || n == nbLigneConclusion) {
					inside = false;
					break;
				} else if (n2 > 1) {
					discussionVec.push_back(currentLine);
				}

			}
		}
	}
	file.close();

	if (param == 1)
		writeDiscussionInFileX(fileName, discussionVec);
	else
		writeDiscussionInFile(fileName, discussionVec);

	if (nbLigneDiscussion != -1)
		getConclusionViaScript(fichierResultat, fileName, n, nbLigneReference);
	else
		getConclusionViaScript(fichierResultat, fileName, nbLigneConclusion, nbLigneReference);	
}


void Structure::getConclusionViaScript(string fichierResultat, string fileName, int nbLigneActuel,int nbLigneReference) {
	// Déclaration
	ifstream file;
	int n = 0;
	int n2=0;
	bool inside = false;
	string currentLine;
	vector<string> conclusionVec;

	file.open(fichierResultat);
	while (!file.eof()) {
		getline(file, currentLine);
		n++;

		if (n == nbLigneActuel || inside) {
			n2++;
			inside = true;
			if ( n == nbLigneReference) {
				inside = false;
				break;
			} else if (n2 > 1) {
				conclusionVec.push_back(currentLine);
			}
		}
	}
	file.close();

	if (param == 1)
		writeConclusionInFileX(fileName, conclusionVec);
	else
		writeConclusionInFile(fileName, conclusionVec);

	getBiblioViaScript(fichierResultat, fileName, nbLigneReference);
}






void Structure::writeIntroductionInFileX(string FileName, vector<string> introduction) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de l'introduction dans le fichier .xml
	out << "\t<introduction>" << endl;
	for (unsigned int index=0; index < introduction.size(); index++)
		out << "\t\t" << introduction[index] << endl;
	out << "\n\t</introduction>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeIntroductionInFile(string FileName, vector<string> introduction) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de l'introduction dans le fichier .xml
	out << "\n\nIntroduction:" << endl;
	for (unsigned int index=0; index < introduction.size(); index++)
		out << "\t" << introduction[index] << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeBodyInFileX(string FileName, vector<string> body) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de body dans le fichier .xml
	out << "\t<body>" << endl;
	for (unsigned int index=0; index < body.size(); index++)
		out << "\t\t" << body[index] << endl;
	out << "\n\t</body>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeBodyInFile(string FileName, vector<string> body) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de body dans le fichier .xml
	out << "\n\nBody:" << endl;
	for (unsigned int index=0; index < body.size(); index++)
		out << "\t"<< body[index] << endl;

	// Fermeture du fichier .xml
	out.close();
}

void Structure::writeDiscussionInFileX(string FileName, vector<string> Discussion) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);

	// Ecriture de body dans le fichier .xml
	out << "\t<Discussion>" << endl;
	for (unsigned int index = 0; index < Discussion.size(); index++)
		out << "\t\t" << Discussion[index] << endl;
	out << "\t</Discussion>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeDiscussionInFile(string FileName, vector<string> Discussion) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);

	// Ecriture de body dans le fichier .xml
	out << "\n\nDiscussion:" << endl;
	for (unsigned int index = 0; index < Discussion.size(); index++)
		out << "\t" << Discussion[index] << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeConclusionInFileX(string FileName, vector<string> conclusion) {
	// Déclaration du flux d'écriture
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de conclusion dans le fichier .xml
	out << "\t<conclusion>" << endl;
	for (unsigned int index=0; index < conclusion.size(); index++)
		out << "\t\t" << conclusion[index] << endl;
	out << "\t</conclusion>" << endl;

	// Fermeture du fichier .xml
	out.close();
}


void Structure::writeConclusionInFile(string FileName, vector<string> conclusion) {
	std::ofstream out;

	// Initialisation du flux de sortie vers le fichier .xml
	out.open(FileName, std::ios::app);
	
	// Ecriture de conclusion dans le fichier .xml
	out << "\n\nConclusion:" << endl;
	for (unsigned int index=0; index < conclusion.size(); index++)
		out << "\t" << conclusion[index] << endl;

	// Fermeture du fichier .xml
	out.close();
}
