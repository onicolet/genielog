#include "Auteur.h"
#include "Titre.h"
#include "Structure.h"

int main(int argc,const char* argv[]) {
	string param		= argv[3];
	Auteur auteur 		= Auteur(param);
	Titre titre 		= Titre(param);
	Structure struc 	= Structure(param);
	string file 		= argv[1];
	string fileName		= argv[2];
	int ligneConclusion = atoi(argv[5]);
	int ligneDiscussion = atoi(argv[4]);
	int ligneReference 	= atoi(argv[6]);

	int AuthorLine = titre.getTitreViaScript(file, fileName);
	auteur.getAuteurViaScript(file, fileName, AuthorLine);
	auteur.getAbstractViaScript(file, fileName);
	struc.getIntroductionViaScript(file, fileName, ligneConclusion, ligneDiscussion, ligneReference); // ca fais le corps / conclusion 
}
