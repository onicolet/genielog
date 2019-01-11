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
	string lineBuffer;
	string tmp;
	string firstWord = currentLine.substr(0, currentLine.find(" "));
	bool foundAName = false;
	//cout << "coucou " <<firstWord << endl;
	// Vérification du premier mot dans le dictionnaire de prénoms
	ifstream fileBis;
	fileBis.open("prenoms.txt");
	while (!fileBis.eof()) {
		getline(fileBis, lineBuffer);
		tmp = lineBuffer.substr(0, lineBuffer.size() - 1);
		if (!currentLine.empty() && firstWord.compare(tmp) == 0) {
			//cout << lineBuffer << endl;
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


int Titre::getTitreViaScript(string fichierResultat, string FileName) {
	// Déclaration des variables
	ifstream file;
	string line;
	vector<string> titre;
	int n = 0;

	// Initialisation
	file.open(fichierResultat);	

	while (!file.eof()) {
		getline(file, line);
		n++;
		if (currentLineContainsFirstName(line)||((currentLineHasURL(line)||currentLineHasANumber(line)) && !titre.empty()))
			break;
		/* La première ligne courante contenant ni chiffre, ni url est considérée comme 
		 * première ligne du titre
		 * */
		if (!line.empty() && !currentLineHasANumber(line) && !currentLineHasURL(line)) {
				titre.push_back(line);
		}
 		
		/* Si la ligne d'après est vide, la zone de titre est considérée comme terminée
		 * */
		//if (line.empty() && !titre.empty())
		  //     break;
	}

	file.close();
	
	if(param == 1)
		writeFileX(FileName,titre);
	else
		writeFile(FileName,titre);

	return n;
}


void Titre::writeFile(string FileName,vector<string> titre) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\nTitle:" << endl;
	 for (unsigned int z = 0; z<titre.size(); ++z)
		 out << "\t" << titre[z] << endl;
	 out << endl;

	 out.close();
}


void Titre::writeFileX(string FileName, vector<string> titre) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\n\t<titre> " << endl;;
	 for (unsigned int z = 0; z<titre.size(); ++z)
		 out << "\n\t\t" << titre[z];
	 out << "\n\t</titre>"<< endl;

	 out.close();
}
