#include "Structure.h"



Structure::Structure()
{
}

Structure::Structure(string par)
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

Structure::~Structure()
{
}

void Structure::getBiblioViaScript(string fichierResultat,string FileName)
{
	ifstream file;
	string line;
	vector<string> reference;
	bool found= false;
	string strcmp1 = "References";
	file.open(fichierResultat);
	while (!file.eof())
	{
		getline(file, line);
		if (line.compare(strcmp1))
			{
				found = true;
				reference.push_back(line);
			}
	}
	file.close();
	if(param == 1)
	{
		writeFileX(FileName,reference);
	}
	else
	{
		writeFile(FileName,reference);
	}
}

void Strucutre::writeFile(string FileName,vector<string> reference)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "biblio = " ;
	 for (unsigned int z = 0; z<titre.size(); ++z)
	 {
		 out << reference[z];
	 }
	 out << endl;
	 out.close();
}


void Strucutre::writeFileX(string FileName,vector<string> reference)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "	<biblio> " ;
	 for (unsigned int z = 0; z<reference.size(); ++z)
	 {
		 out << reference[z];
	 }
	 out << "</biblio>"<< endl;
	 out.close();
}