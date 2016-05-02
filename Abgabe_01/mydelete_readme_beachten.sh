#!/bin/sh
for f in /home/mi1373/BS/Aufgabenblatt_01/*
do 
if test -r $f; then
	echo "Wollen Sie die Datei $f entfernen? j/n"
	read word
	case $word in
		j* )
		rm $f
		echo "Die Datei $f wurde entfernt"
		;;
		n* )
		echo "Die Datei $f wurde nicht geloescht"
		;;	
	esac
else
echo "Die Datei $f wurde nicht gefunden"
fi
done
echo "Das Programm wird geschlossen"
