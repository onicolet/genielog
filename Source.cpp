#include "Auteur.h"
#include "Titre.h"

int main(int argc,const char* argv[])
{
	Auteur auteur = Auteur();
	Titre titre = Titre();
	string file = argv[1];
	//file = "Vanderwende_2007_Beyond SumBasic.txt";
	auteur.getAuteursViaScript(file);
	cout << endl << endl;
	titre.getTitreViaScript(file);
	getchar();

}