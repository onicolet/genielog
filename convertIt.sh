#! /bin/bash


cd $1

if [ ! -d "CONVERT" ];then
	mkdir "CONVERT"
fi

if [ ! -d "PARSE" ];then
	mkdir "PARSE"
fi



for file in *.pdf
do
	nameFile=`basename "$file" ".pdf"`".txt"
	
	#A executer sur le raspberry
	pdf2txt.py  -p 1 -V -o "CONVERT/$nameFile" "$file"
	#pdf2txt  -V -o "CONVERT/$nameFile" "$file"
	echo "$file" > "PARSE/$nameFile"
	
	"../genielog/convertIt" "CONVERT/$nameFile" "PARSE/$nameFile"	

done
