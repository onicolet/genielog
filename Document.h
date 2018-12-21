#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std; 

class Document
{
public:
	String nomDocument;
private:
	String getNomDocument();
	void getNomDocumentViaScript();
}