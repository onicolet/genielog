#include "Auteur.h"



string * Auteur::getAuteurs()
{
	return NULL;
}

void Auteur::getAuteursViaScript(string fichierResultat,string FileName)
{
	ifstream file;
	bool found = false;
	string line; 
	vector<string> abstract;
	string cmp1 = "Abstract";
	file.open(fichierResultat);
	int i = 0;
	int j = 0;
	while (! file.eof())
	{
		getline(file, line);

		if (cmp1.compare(line)==0 || found)
		{
			found = true;
			if (line.empty() && !abstract.empty())
			{
				break; 
			}
			else
			{ 	if(i!=0)
				{abstract.push_back(line);}
				cout << "add" << i << endl;
				i++;
			}
		}
	}
	// for (unsigned int z = 0; z<abstract.size(); ++z)
	// {
	// 	cout << abstract[z];
	// 	//process on el...
	// }
	file.close();
	writeFile(FileName,abstract);
}

void Auteur::writeFile(string FileName,vector<string> abstract)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "abstract = " ;
	 for (unsigned int z = 0; z<abstract.size(); ++z)
	 {
		 out << abstract[z];
	 }
	 out.close();
}
Auteur::Auteur()
{
}


Auteur::~Auteur()
{
}
