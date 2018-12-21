#include "Titre.h"



Titre::Titre()
{
}


Titre::~Titre()
{
}

void Titre::getTitreViaScript(string fichierResultat)
{

	ifstream file;
	string line;
	vector<string> abstract(10);
	string cmp1 = "Abstract";
	file.open(fichierResultat);
	int i = 0;
	int j = 0;
	while (!file.eof())
	{
		getline(file, line);
			if (i==1)
			{
				abstract.push_back(line);
				break;
				//cout << "add" << i << endl;
			}
		
			i++;
	}
	for (unsigned int z = 0; z<abstract.size(); ++z)
	{
		cout << abstract[z];
	}
	file.close();
}
