#include "Structure.h"



Structure::Structure() {}


Structure::Structure(string par) {
	if(par.compare("-x") == 0)
		param = 1 ;	
	else
		param = 2;
}


Structure::~Structure() {}


void Structure::getBiblioViaScript(string fichierResultat, string FileName) {
	ifstream file;
	string line, strcmp1 = "References";
	vector<string> reference;
	bool found = false;
	
	file.open(fichierResultat);
	
	while (!file.eof()) {
		getline(file, line);
		if (line.compare(strcmp1)==0 || found){
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

	 out << "\nBibliography: ";
	 for (unsigned int z = 0; z<reference.size(); ++z)
		 out << reference[z];

	 out << endl;
	 out.close();
}


void Structure::writeFileX(string FileName,vector<string> reference) {
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "\n\t<biblio> ";
	
	 for (unsigned int z = 0; z<reference.size(); ++z)
		 out << "\n\t\t"  << reference[z];

	 out << "\n\t</biblio>" << endl;
	 out.close();
}
