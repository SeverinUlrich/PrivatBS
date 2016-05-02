#!/usr/bin/sh
realname=$(finger $USER | head -1 | cut -d: -f3)
hour=$(date +"%H")
zeit=$(date +"%H:%M") 
if [ $hour -ge "6" ] && [ $hour -lt "9" ]; then 
msg="Morgen" 
elif [ $hour -ge "9" ] && [ $hour -lt "15" ]; then 
msg="Tag"  
elif [ $hour -ge "15" ] && [ $hour -lt "18" ]; then 
msg="Nachmittag" 
elif [ $hour -ge "18" ] && [ $hour -lt "23" ]; then 
msg="Abend" 
fi 
echo "Guten $msg $realname, es ist $zeit Uhr." 
