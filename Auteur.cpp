#include "Auteur.h"


Auteur::Auteur(string par)
{
	if(par.compare("-x") == 0)
	{
		param = 1;
	}
	else
	{
		param = 2;
	}
}

void Auteur::getAuteurViaScript(string fichierResultat,string FileName)
{
	ifstream file;
	string line; 
	vector<string> auteur;
	string cmp1 = "Abstract";
	string cmp2 = "ABSTRACT";
	file.open(fichierResultat);
	string strcompare;
	int i=0;
	while (! file.eof())
	{
		getline(file, line);
		strcompare = line.substr (0,8);
		if (cmp1.compare(strcompare)==0 || cmp2.compare(strcompare)==0)
		{
			break;
		}
			if(i!=0)
				{auteur.push_back(line);}
				i++;
	}
	file.close();
	if(param == 1)
	{
		writeFileAuteurX(FileName,auteur);
	}
	else
	{
		writeFileAuteur(FileName,auteur);
	}
}

void Auteur::getAbstractViaScript(string fichierResultat,string FileName)
{
	ifstream file;
	bool found = false;
	string line; 
	vector<string> abstract;
	string cmp1 = "Abstract";

	string cmp2= "ABSTRACT";
	file.open(fichierResultat);
	string strcompare;
	int i=0;
	while (! file.eof())
	{
		getline(file, line);
		strcompare = line.substr (0,8);

		if ((cmp1.compare(strcompare)==0||cmp2.compare(strcompare)==0) || found)

		{
			found = true;
			if (line.empty() && !abstract.empty())
			{
				break; 
			}
			else if(!line.empty())
			{ 	if(i!=0)
				{abstract.push_back(line);}
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
	if(param == 1)
	{
		writeFileAbstractX(FileName,abstract);
	}
	else
	{
		writeFileAbstract(FileName,abstract);
	}
}

void Auteur::writeFileAbstract(string FileName,vector<string> abstract)
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

void Auteur::writeFileAuteur(string FileName,vector<string> auteur)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "Auteur = " ;
	 for (unsigned int z = 0; z<auteur.size(); ++z)
	 {
		 out << auteur[z];
	 }
	 out.close();
}


void Auteur::writeFileAbstractX(string FileName,vector<string> abstract)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "	<abstract> " ;
	 for (unsigned int z = 0; z<abstract.size(); ++z)
	 {
		 out << abstract[z];
	 }
	 out << "</abstract> " << endl;
	 out.close();
}

void Auteur::writeFileAuteurX(string FileName,vector<string> auteur)
{
	 std::ofstream out;
	 out.open(FileName, std::ios::app);

	 out << "	<auteur> " ;
	 for (unsigned int z = 0; z<auteur.size(); ++z)
	 {
		 out << auteur[z];
	 }
	 out << "</auteur> "<< endl;
	 out.close();
}



Auteur::Auteur()
{
}


Auteur::~Auteur()
{
}
