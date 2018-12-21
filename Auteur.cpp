#include "Auteur.h"

void Titre::getAuteurViaScript(char* fichierResultat)
{
	int f = open(fichierResultat, O_WRONLY|O_APPEND,0777);
	close(1);
	dup(f);
	execlp("ls", "ls", repertoire, NULL);
}

String Titre::getAuteur()
{
	return this.nomAuteur;
}