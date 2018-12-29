#include "Auteur.h"
#include "Titre.h"
#include "Structure.h"

int main(int argc,const char* argv[])
{
	string param = argv[3];
	Auteur auteur = Auteur(param);
	Titre titre = Titre(param);
	Structure struc = Structure(param);
	string file = argv[1];
	string fileName= argv[2];
	//cout << file << endl;
	titre.getTitreViaScript(file,fileName);
	struc.getBiblioViaScript(file,fileName);
	auteur.getAbstractViaScript(file,fileName);
	//file = "Vanderwende_2007_Beyond SumBasic.txt";
	auteur.getAuteurViaScript(file,fileName);


}
