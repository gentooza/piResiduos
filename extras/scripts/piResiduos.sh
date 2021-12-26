#!/bin/bash

##PATH
#PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SCRIPT=$(readlink -f $0)
SCRIPT_PATH=`dirname $SCRIPT`
echo "$SCRIPT_PATH"
cd $SCRIPT_PATH/bioreciclaje
##ssh tunnel
myPID=$(ps -ef | grep "ssh -f -L 3307:localhost:3306 biogesin@biogesin.bioreciclaje.es -N" | awk '{print $2}' | head -1)
kill $myPID
ssh -f -L 3307:localhost:3306 biogesin@biogesin.bioreciclaje.es -N -i $SCRIPT_PATH/ssh_miramundo
##
##libraries
export LD_LIBRARY_PATH=$SCRIPT_PATH/bioreciclaje/lib:$LD_LIBRARY_PATH
##
##server
killall piResiduos
DATE=`date +%T`".log"
mkdir logs
./piResiduos > ./logs/${DATE} &
##
#cd /home/test/
##client
pvbrowser
##
wait

