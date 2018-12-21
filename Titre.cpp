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
	string titre;
	file.open(fichierResultat);
	while (!file.eof())
	{
		getline(file, line);
			if (!line.empty())
			{
				titre=line;
				break;
			}
	}

	cout << titre;
	file.close();
	writeFile(FileName,titre);
}

void Titre::writeFile(string FileName,string titre)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "file name ="<<titre<<endl;
	 out.close();
}