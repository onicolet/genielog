#include "Auteur.h"



string * Auteur::getAuteurs()
{
	return nullptr;
}

void Auteur::getAuteursViaScript(string fichierResultat)
{
	ifstream file;
	bool found = false;
	string line; 
	vector<string> abstract(100);
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
			if (line.empty())
			{
				j++;
				if (j == 2){ break; }
			}
			else
			{
				abstract.push_back(line);
				//cout << "add" << i << endl;
				i++;
			}
		}
	}
	for (unsigned int z = 0; z<abstract.size(); ++z)
	{
		cout << abstract[z];
		//process on el...
	}
	file.close();

}

Auteur::Auteur()
{
}


Auteur::~Auteur()
{
}
