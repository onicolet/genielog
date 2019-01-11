#!/bin/bash


# Affichage du titre
clear all

echo "
  _                       ___ ___ 
 /   _  ._      _  ._ _|_  |   |  
 \_ (_) | | \/ (/_ |   |_ _|_  |  


"

# Définition des répertoires source
pwdExec=`pwd`		# Répertoire de lancement de l'exécutable
pwdPDF=`pwd $1`"/$1"	# Répertoire contenant les fichiers pdf à parser
# Variable contenant le chemin absolu du répertoire de destination
destRep=$pwdPDF
# Variable contenant le chemin absolu vers le répertoire contenant les 
# sorties brutes
srcRep=$pwdPDF"CONVERT/"


# Définition du répertoire de destination
if [ $2 = "-x" ]
then
	destRep="$destRep""XML/"
elif [ $2 = "-t" ]
then
	destRep="$destRep""TXT/"
fi
# Création du dossier contenant les sorties de pdf2txt, s'il 
# n'existait pas.
if [ ! -d $1"CONVERT" ]
then
	mkdir "$srcRep"
fi
# Contient les fichiers txt parsés
if [ ! -d $destRep ]
then
	mkdir "$destRep"
fi


# Choix de tout parser
parseAll="none"
while [ $parseAll != "o" -a $parseAll != "n" ]
do
	read -p "Souhaitez-vous parser tout le contenu du dossier $pwdPDF ? (o/n)
	--?--> " parseAll
			
	if [ $parseAll != "n" -a $parseAll != "o" ]
	then
		echo "Veuillez choisir o ou n pour faire votre choix!"
		
	fi
done


# tableau contenant les noms et chemin des fichiers pdf à parser
declare -a tab
parsingIndex=0


# Si on parse tout
if [ $parseAll = "o" ] 
then
	for file in "$pwdPDF"*.pdf
	do
		tab[$parsingIndex]="$file"
		let parsingIndex=$parsingIndex+1
	done
else
	# Pour affichage de la liste des fichiers et compter le nombre total de fichier dans le dossier
	fileIndex="1"

	for file in "$pwdPDF"*.pdf
	do
		fileNameToDisplay=`echo $file | tr "/" "\n" | tail -1`
		echo "$fileIndex: $fileNameToDisplay"
		echo -e $fileIndex":"$file >> listeFile.txt
		let fileIndex=$fileIndex+1
	done

	# Demande à l'utilisateur l'index du fichier a parser (saisie terminée par -1)
	while [ "$answer" !=  "-1" ]
	do
		read -p "	--?--> Indice du fichier à parser (-1 pour lancer le parsing): " answer
		if [ "$answer" == "-1" ]
		then
			echo -e "\n\n--INFO--> Lancement du parsing...\n\n"
		elif [ "$answer" -lt "$fileIndex" -a "$answer" -gt "0" ]
		then
			pdf="`cat listeFile.txt | head -n $answer | tail -n 1 | cut -f2 -d":"`"
			tab[$parsingIndex]="$pdf"
			let parsingIndex=$parsingIndex+1	
		else
			echo -e "--WARN--> Mauvaise entrée, veuillez réessayer..."
		fi
	done


	# for f in "${tab[@]}"
	# do
	# 	echo $f
	# done


	rm -f ./listeFile.txt
fi


for file in "${tab[@]}"
do
	echo -e "--INFO--> Traitement du fichier:\n$file ...\n"
	if [ "$2" == "-x" ]
	then
		fileNameBuffer=`basename "$file" ".pdf"`".txt"
		fileNameFinal=`basename "$fileNameBuffer" ".txt"`".xml"

		#A executer sur le raspberry
		#pdf2txt.py -V -o "$srcRep$fileNameBuffer" "$file"
		pdftotext "$file" "$srcRep$fileNameBuffer"

		# Initialisation du fichier de sortie
		echo -e "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" > "$destRep$fileNameBuffer"
		echo "<article>" >> "$destRep$fileNameBuffer"
		echo -e "\t<preamble>\n\t\t$file\n\t</preamble>" >> "$destRep$fileNameBuffer"
			
	elif [ "$2" == "-t" ]
	then
		fileNameBuffer=`basename "$file" ".pdf"`".txt"

		# A décommenter pour exécution sur le Raspberry
		#pdf2txt.py -V -o "CONVERT/$fileNameBuffer" "$file"

		# A décommenter pour exécuter sur les machines du CERI
		pdftotext "$file" "$srcRep$fileNameBuffer"

		echo -e "Preamble:\n$file\n" > "$destRep$fileNameBuffer"
	else
		echo -e "--WARN--> Exécutez avec -t pour une sortie texte ou -x pour une sortie xml"
		exit
	fi
	
	
	# Première ligne de la section de Discussion
	discussionLine=`cat "$srcRep$fileNameBuffer" | egrep -n "Discussion|DISCUSSION" | cut -f1 -d":" | tail -n1`
	if [ "$discussionLine" = "" ]
	then
		discussionLine="-1";
	fi
	# Recherche de la ligne contenant la conclusion
	conclusionLine=`cat "$srcRep$fileNameBuffer" | egrep -n "Conclusion|CONCLUSION" | cut -f1 -d":" | tail -n1`	
	# Première ligne de la section Bibliographique
	referencesLine=`cat "$srcRep$fileNameBuffer" | egrep -n "Reference|REFERENCE" | cut -f1 -d":" | tail -n1`
		
	./convertIt "$srcRep$fileNameBuffer" "$destRep$fileNameBuffer" "$2" "$discussionLine" "$conclusionLine" "$referencesLine"
	
	# echo -e "--INFO--> Index du résumé:\t\t" $abstractLine
	# echo -e "--INFO--> Index de la discussion:\t" $discussionLine
	# echo -e "--INFO--> Index de la conclusion:\t" $conclusionLine
	# echo -e "--INFO--> Index de la bibliographie:\t $referencesLine \n"

	if [ "$2" == "-x" ]
	then
		echo -e "\n</article>" >> "$destRep$fileNameBuffer"
		# On renomme l'extension du fichier
		mv "$destRep$fileNameBuffer" "$destRep$fileNameFinal"
	fi

	rm -f listFile.txt
done
