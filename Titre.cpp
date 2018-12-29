#include "Titre.h"



Titre::Titre()
{
}

Titre::Titre(string par)
{
	if(par.compare("-x"))
	{
		param = 1 ;	
	}
	else
	{
		param = 2;
	}
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
	if(param == 1)
	{
		writeFileX(FileName,titre);
	}
	else
	{
		writeFile(FileName,titre);
	}
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


void Titre::writeFileX(string FileName,vector<string> titre)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "	<titre> " ;
	 for (unsigned int z = 0; z<titre.size(); ++z)
	 {
		 out << titre[z];
	 }
	 out << "</titre>"<< endl;
	 out.close();
}