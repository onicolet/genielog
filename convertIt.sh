#! /bin/bash


cd $1

if [ ! -d "CONVERT" ]
then
	mkdir "CONVERT"
elif [ ! -d "PARSE" ]
then
	mkdir "PARSE"
elif [ ! -d "XML" ]
then
	mkdir "XML"
fi


var="$2"

if [ "$var" == "-x" ]
then
	for file in *.pdf
	do
		fileNameBuffer=`basename "$file" ".pdf"`".data"
		fileNameFinal=`basename "$file" ".pdf"`".xml"

		#A executer sur le raspberry
		pdf2txt.py -V -o "CONVERT/$fileNameBuffer" "$file"
		#pdf2txt  -V -o "CONVERT/$fileNameBuffer" "$file"

		# Initialisation du fichier de sortie
		echo -e "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" > "XML/$fileNameBuffer"
		echo "<article>" >> "XML/$fileNameBuffer"
		echo -e "\t<preamble> $file </preamble>" >> "XML/$fileNameBuffer"
		"../genielog/convertIt" "CONVERT/$fileNameBuffer" "XML/$fileNameBuffer" "$2"
		echo -e "\n</article>" >> "XML/$fileNameBuffer"
		
		# On renomme l'extension du fichier
		mv "XML/$fileNameBuffer" "XML/$fileNameFinal"
	done 
elif [ "$var" == "-t" ]
then
	for file in *.pdf
	do
		nameFile=`basename "$file" ".pdf"`".txt"
	
		#A executer sur le raspberry
		pdf2txt.py -V -o "CONVERT/$nameFile" "$file"
		#pdf2txt  -V -o "CONVERT/$nameFile" "$file"
		echo "$file" > "PARSE/$nameFile"
		
		"../genielog/convertIt" "CONVERT/$nameFile" "PARSE/$nameFile" "$2"	
	done
else
	echo "Exécutez avec -t pour une sortie texte ou -x pour une sortie xml"
fi
