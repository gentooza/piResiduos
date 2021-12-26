#!/bin/bash

##ssh tunnel
myPID=$(ps -ef | grep "ssh -f -L 3307:localhost:3306 biogesin@biogesin.bioreciclaje.es -N" | awk '{print $2}' | head -1)
kill $myPID


