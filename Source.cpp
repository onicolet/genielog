#include "Auteur.h"
#include "Titre.h"

int main(int argc,const char* argv[])
{
	Auteur auteur = Auteur();
	Titre titre = Titre();
	string file = argv[1];
	string fileName= argv[2];
	cout << file << endl;
	titre.getTitreViaScript(file,fileName);
	cout << endl << endl;
	//file = "Vanderwende_2007_Beyond SumBasic.txt";
	auteur.getAuteursViaScript(file,fileName);
	getchar();
}
