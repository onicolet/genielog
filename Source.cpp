#include "Auteur.h"
#include "Titre.h"
#include "Structure.h"

int main(int argc,const char* argv[]) {
	string param 	= argv[3];
	Auteur auteur	= Auteur(param);
	Titre titre 	= Titre(param);
	Structure struc = Structure(param);
	string file 	= argv[1];
	string fileName	= argv[2];
	int ligne = atoi(argv[4]);

	titre.getTitreViaScript(file, fileName);
	auteur.getAuteurViaScript(file, fileName);
	auteur.getAbstractViaScript(file, fileName);
	struc.getCorpsViaScript(file, fileName, ligne);
	struc.getBiblioViaScript(file, fileName);
}
