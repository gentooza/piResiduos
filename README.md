# Pixelada S. Coop. and. Fork of piResiduos
garbage managing software, (currently only in spanish) we have several local nodes managing input/ouput materials, and a central administration server.
developed using pvbrowser(https://github.com/pvbrowser/pvb) SCADA framework.

## dependencies
+ libharu >= 2.3.0
+ SmtpClient-for-Qt (https://github.com/bluetiger9/SmtpClient-for-Qt) as submodule inside lib folder.
+ pvbrowser (pvslib and rllib)
+ boost

## remote database connection and web administration page
piResiduos is developed for working with a central remote MySQL database in mind, you'll need a VPS and it's connections for tunneling the database (SSH) and being able to syncronize, update, share, etc.

Also there will be files app will backup via SSH tunneling.

You'll have to configure this connection in config.ini, in piResiduos.sh, in extra/scripts... files and in generic_tools.cpp (function int copy_files_to_remote_server(std::string folder_in_backup))

put the ssh key for example in extras/ .

for building the local database execute in terminal it's creations cript

    sqlite3 bio.db < bio.sqlite3

## remote server database structure

see file bio.remote.

## hardware needed
It was first designed using a privative signing pad, it has been removed in this free version, now I think I would use a software signing pad using dual screens.

It uses scales, and we communicate it using a basic rs232 serial protocol, sending a command and receiving the weight. (we use boost, is easy to understand it protocol seeing source code) You can bypass it inserting plate by hand.

It uses privative cameras for taking plates from trucks, they are from a Spanish company bad for free software but also technical support, so we have developed our own library using it's http API. You can bypass it inserting plate by hand.

## Compile and execute
It has been developed only for GNU/Linux, it's working now for real under ubuntu 16.04 (xenial)

Once dependencies are installed or compiled and linked.

    qmake
    make
    sh piResiduos.sh

Happy Hacking!

## license and copyright
 This file is part of PiResiduos.

 Copyright 2017-2019, Pro Integra SL
 Copyright 2019-2021, Pixelada S. Coop. And.

 PiResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 PiResiduos is distributed in the hope that it will
 be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with PiResiduos.
 If not, see <https://www.gnu.org/licenses/>.