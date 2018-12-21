#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std; 

class Auteur
{
public:
	String nomAuteurs;
private:
	String getAuteurs();
	void getAuteursViaScript();
}