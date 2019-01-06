#include "Titre.h"



Titre::Titre() {}


Titre::Titre(string par) {
	if (par.compare("-x") == 0)
		param = 1 ;	
	else
		param = 2;
}


Titre::~Titre() {}

//Vérifie si la ligne passée en paramètre contient un chiffre
bool currentLineHasANumber(string curLine){
	return (curLine.find_first_of("0123456789") != std::string::npos);
}

bool currentLineHasURL(string curLine){
	return (curLine.find(".com") != std::string::npos ||
		curLine.find(".fr") != std::string::npos ||
		curLine.find("www") != std::string::npos ||
		curLine.find(".de") != std::string::npos ||
		curLine.find("http") != std::string::npos ||
		curLine.find(".org") != std::string::npos ||
		curLine.find(".gouv") != std::string::npos);
}


bool currentLineContainsFirstName(string currentLine) {
	// Déclaration
	string lineBuffer, firstWord=currentLine.substr(0, currentLine.find(" "));
	bool foundAName = false;

	// Vérification du premier mot dans le dictionnaire de prénoms
	ifstream fileBis;
	fileBis.open("../genielog/prenoms.txt");
	while (!fileBis.eof()) {
		getline(fileBis, lineBuffer);
		if (firstWord.compare(lineBuffer) == 0) {
			foundAName = true;
			break;
		}
	}
	fileBis.close();

	return foundAName;
}


bool startsWithCapitalLetter(string currentLine) {
	char c = currentLine.at(0);
	return (c >= 'A' && c <= 'Z')?true:false;
}


void Titre::getTitreViaScript(string fichierResultat, string FileName) {
	// Déclaration des variables
	ifstream file;
	string line;
	vector<string> titre;

	// Initialisation
	file.open(fichierResultat);	

	while (!file.eof()) {
		getline(file, line);

		/* La première ligne courante contenant ni chiffre, ni url est considérée comme 
		 * première ligne du titre
		 * */
		if (!line.empty() 
		&& !currentLineHasANumber(line) 
		&& !currentLineHasURL(line)) {
			if (startsWithCapitalLetter(line) && currentLineContainsFirstName(line))
				break;
			else
				titre.push_back(line);
		}

		/* Si la ligne d'après est vide, la zone de titre est considérée comme terminée
		 * */
		if (line.empty() && !titre.empty())
		       break;
	}

	file.close();
	
	if(param == 1)
		writeFileX(FileName,titre);
	else
		writeFile(FileName,titre);
}


void Titre::writeFile(string FileName,vector<string> titre) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "Title : " ;
	 for (unsigned int z = 0; z<titre.size(); ++z)
		 out << titre[z];

	 out << endl;
	 out.close();
}


void Titre::writeFileX(string FileName, vector<string> titre) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\t<titre> " ;
	 for (unsigned int z = 0; z<titre.size(); ++z)
		 out << "\n\t\t" << titre[z];

	 out << "\n\t</titre>"<< endl;
	 out.close();
}
