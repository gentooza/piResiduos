#!/bin/bash

#  PiResiduos
#
#  Copyright 2016,2017 by it's authors. 
#
#  Some rights reserved. See COPYING, AUTHORS.
#  This file may be used under the terms of the GNU General Public
#  License version 3.0 ,or any later version of GPL, as published by the Free Software Foundation
#  and appearing in the file COPYING included in the packaging of
#  this file.
#
#  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
#  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


SCRIPT=$(readlink -f $0)
SCRIPT_PATH=`dirname $SCRIPT`
##ssh tunnel
#ssh-add extras/ssh_miramundo
myPID=$(ps -ef | grep "3307:localhost:3306 biogesin@biogesin.bioreciclaje.es -N" | awk '{print $2}' | head -1)
kill $myPID
ssh -f -L 3307:localhost:3306 biogesin@biogesin.bioreciclaje.es -N
#autossh -M 20000 -f -L 3307:localhost:3306 biogesin@biogesin.bioreciclaje.es -N
##
##libraries
export LD_LIBRARY_PATH=$SCRIPT_PATH/lib:$LD_LIBRARY_PATH
##
##server
# gdb ./piResiduos
# valgrind --leak-check=full ./piResiduos
# valgrind ./piResiduos
valgrind --track-origins=yes ./piResiduos
#./piResiduos &
#sleep 1
#pvbrowser
##
