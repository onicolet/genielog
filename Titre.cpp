#include "Titre.h"



Titre::Titre()
{
}


Titre::~Titre()
{
}

void Titre::getTitreViaScript(string fichierResultat,string FileName)
{

	ifstream file;
	string line;
	vector<string> titre;
	file.open(fichierResultat);
	while (!file.eof())
	{
		getline(file, line);
			if (!line.empty())
			{
				titre.push_back(line);
				break;
			}
	}

	file.close();
	writeFile(FileName,titre);
}

void Titre::writeFile(string FileName,vector<string> titre)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "Titre = " ;
	 for (unsigned int z = 0; z<titre.size(); ++z)
	 {
		 out << titre[z];
	 }
	 out << endl;
	 out.close();
}