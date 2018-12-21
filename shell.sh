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
	pdf2txt  -o "CONVERT/$nameFile" "$file"
	echo "$file" >> "PARSE/$nameFile"
		
done
