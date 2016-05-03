#!/bin/sh
for f in $*
do ./myquestion.sh "Haben Sie die Frage verstanden? Ja/Nein";  
if [ $? -eq 0 ]
	then
		rm $f;
		echo "Die Datei $f wurde entfernt"
	else
		echo "Die Datei $f wurde nicht geloescht"
fi
done
echo "Das Programm wird geschlossen"
