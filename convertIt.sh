#!/bin/bash

echo "
                          ___ ___ 
 /   _  ._      _  ._ _|_  |   |  
 \_ (_) | | \/ (/_ |   |_ _|_  |  
"


cd $1

#contient les fichiers txt brut
if [ ! -d "CONVERT" ]
then
	mkdir "CONVERT"
fi
#Contient les fichiers txt parsés
if [ ! -d "TXT" ]
then
	mkdir "TXT"
fi
#contient les fichiers xml parsés
if [ ! -d "XML" ]
then
	mkdir "XML"
fi


var="$2"
rep="PARSE"

indice="1"

rm listeFile.txt

for file in *.pdf
do
	echo $indice $file
	echo -e $indice":"$file >> listeFile.txt
	let indice=$indice+1
done


declare -a tab
i=0

# Demande à l'utilisateur l'index du fichier a parser, finis par -1
while [ "$answer" !=  "-1" ]
do
	read -p "Entrez un numéro de fichier à parser, ou -1 pour lancer le parsing: " answer
	if [ "$answer" == "-1" ]
	then
		echo "Lancement du parsing"
	elif [ "$answer" -lt "$indice" -a "$answer" -gt "0" ]
	then
		pdf="`cat listeFile.txt | head -n $answer | tail -n 1 | cut -f2 -d":"`"
		tab[$i]="$pdf"
		let i=$i+1	
	else
		echo "Mauvaise entrée"
	fi
done

for f in "${tab[@]}"
do
	echo $f
done


for file in "${tab[@]}"
do
	echo "Traitement du fichier: "$file
		if [ "$var" == "-x" ]
		then
			rep="XML"
			fileNameBuffer=`basename "$file" ".pdf"`".data"
			fileNameFinal=`basename "$fileNameBuffer" ".data"`".xml"

			#A executer sur le raspberry
			#pdf2txt.py -V -o "CONVERT/$fileNameBuffer" "$file"
			pdf2txt  -V -o "CONVERT/$fileNameBuffer" "$file"

			# Initialisation du fichier de sortie
			echo -e "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" > "XML/$fileNameBuffer"
			echo "<article>" >> "XML/$fileNameBuffer"
			echo -e "\t<preamble> \n\t\t$file \n\t</preamble>" >> "XML/$fileNameBuffer"
			
		elif [ "$var" == "-t" ]
		then
			rep="TXT"
			fileNameBuffer=`basename "$file" ".pdf"`".txt"

			#A executer sur le raspberry
			#pdf2txt.py -V -o "CONVERT/$fileNameBuffer" "$file"
			pdf2txt  -V -o "CONVERT/$fileNameBuffer" "$file"
			echo "Preamble: $file" > "$rep/$fileNameBuffer"
		else
			echo "Exécutez avec -t pour une sortie texte ou -x pour une sortie xml"
			exit
		fi
		
		ConclusionLine=`cat "CONVERT/$fileNameBuffer" | egrep -n "Conclusion|CONCLUSION" | cut -f1 -d":" | tail -n 1`
		./../genielog/convertIt "CONVERT/$fileNameBuffer" "$rep/$fileNameBuffer" "$2" $ConclusionLine
		echo "Conclusion ligne: " $ConclusionLine
		if [ "$2" == "-x" ]
		then
			echo -e "\n</article>" >> "XML/$fileNameBuffer"
			# On renomme l'extension du fichier
			mv "$rep/$fileNameBuffer" "$rep/$fileNameFinal"
		fi
done

