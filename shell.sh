#! /bin/bash
if [ ! -d "CONVERT" ];then
	mkdir "CONVERT"
fi

if [ ! -d "PARSE" ];then
	mkdir "PARSE"
fi

cd $1
for file in *.pdf
do
	nameFile=`basename "$file" ".pdf"`".txt"
	pdf2txt  -o "../CONVERT/$nameFile" "$file" 
done
