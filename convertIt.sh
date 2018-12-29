#! /bin/bash

echo "
  _                       ___ ___ 
 /   _  ._      _  ._ _|_  |   |  
 \_ (_) | | \/ (/_ |   |_ _|_  |  
"


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
rep="PARSE"

for file in *.pdf
do
	# Demande à l'utilisateur s'il souhaite parser le fichier courant
	read -p "Voulez-vous parser $file ? (y/n) " answer
	while [ "$answer" != "y" ] && [ "$answer" != "yes" ] && [ "$answer" != "n" ] && [ "$answer" != "no" ]
	do
		echo "Mauvaise entrée, réessayez à nouveau"
		read -p "Voulez-vous parser $file ? (y/n) " answer
	done
	if [ "$answer" == "y" ] || [ "$answer" == "yes" ]
	then

		if [ "$var" == "-x" ]
		then
			fileNameBuffer=`basename "$file" ".pdf"`".data"
			fileNameFinal=`basename "$file" ".pdf"`".xml"

			#A executer sur le raspberry
			pdf2txt.py  -p 1 -V -o "CONVERT/$fileNameBuffer" "$file"
			#pdf2txt  -V -o "CONVERT/$fileNameBuffer" "$file"

			# Initialisation du fichier de sortie
			echo -e "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" > "XML/$fileNameBuffer"
			echo "<article>" >> "XML/$fileNameBuffer"
			echo -e "\t<preamble> $file </preamble>" >> "XML/$fileNameBuffer"
			echo -e "\n</article>" >> "XML/$fileNameBuffer"
			rep="XML"
			# On renomme l'extension du fichier
			mv "XML/$fileNameBuffer" "XML/$fileNameFinal"
		elif [ "$var" == "-t" ]
		then
			nameFile=`basename "$file" ".pdf"`".txt"
	
			#A executer sur le raspberry
			pdf2txt.py  -p 1 -V -o "CONVERT/$nameFile" "$file"
			#pdf2txt  -V -o "CONVERT/$nameFile" "$file"
			echo "$file" > "PARSE/$nameFile"
		else
			echo "Exécutez avec -t pour une sortie texte ou -x pour une sortie xml"
		fi
		"../genielog/convertIt" "CONVERT/$fileNameBuffer" "$rep/$fileNameBuffer" "$2"
	fi
done

