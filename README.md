# piResiduos

Garbage managing software, (currently only in spanish) we have several local nodes managing input/ouput materials, and a central administration server -no source code available for this pieze ;-(-.

This is the source code for every local node. It's developed using C++ and [pvbrowser](https://github.com/pvbrowser/pvb) SCADA framework.

## History

It was created at 2016 by the industrial, and now defunct, company [Pro Integra S.L.](http://prointegra.es/) , afterwards, development was moved at 2019 to the Software Development Company [Pixelada S. Coop. And.](https://pixelada.org)

Since 2023, It's developed under collaboration between the costumer, El Alambre Estudio Creativo S. Coop. And. and the University of Córdoba.

## Dependencies

+ [libharu](https://github.com/libharu/libharu) >= 2.3.0
+ [SmtpClient-for-Qt](https://github.com/bluetiger9/SmtpClient-for-Qt) as submodule inside lib folder.
+ [pvbrowser](https://pvbrowser.de) (pvslib and rllib)
+ boost
+ cups
+ QT5 -sqlite3, mysql... modules-
+ -optional- valgrind for debugging.

Version 0.2 is intended to work under Ubuntu GNU/Linux 16.04 -QT4 version of pvbrowser-
Version 0.3, the currently active main branch, is developed for working under Ubuntu GNU/Linux 22.04 using QT5 and the last pvbrowser version.

## Remote database connection and web administration page

pixResiduos is developed for working with a central remote MySQL database in mind, you'll need a VPS and it's connections for tunneling the database (SSH) and being able to syncronize, update, share, etc.

Also there will be files app will backup via SSH tunneling.

You'll have to configure this connection in: *config.ini*, *piResiduos.sh*, */extra/scripts...* files and in *generic_tools.cpp* -function *int copy_files_to_remote_server(std::string folder_in_backup)*-

put the ssh key for example in *extras/*.

We are currently working in using an API for avoiding this old method.

## Local Database

For syncing and store middle data the app uses a sqlite3 database.

For building the local database execute in terminal it's creations cript:

```
sqlite3 bio.db < bio.sqlite3
```

## Remote server database structure

see file *bio.remote*. -Maybe is not updated enough!-

## Hardware needed

It was first designed using a privative signing pad, it has been removed in this free version, now I think I would use a software signing pad using dual screens.

It uses scales, and we communicate it using a basic rs232 serial protocol, sending a command and receiving the weight. (we use boost, is easy to understand it protocol seeing source code) You can bypass it inserting plate by hand.

It uses privative cameras for taking plates from trucks, they are from a (now vanished) Spanish company with null intereset in free software and no technical support, so we have developed our own library using it's http API. You can bypass it inserting plate by hand.

## Compile and execute

It has been developed only for GNU/Linux, it's working now for real under ubuntu 22.04 -jammy-

Once dependencies are installed or compiled and linked.
```
qmake
make
sh piResiduos.sh
```

Alternatively, you can debug using valgrind with the script:
```
sh piResiduos-DEBUG.sh
```

And opening the client in another terminal
```
pvbrowser
```
Happy Hacking!

## License and copyright
```
 This file is part of PixResiduos.

 Copyright 2021, Pixelada S. Coop. And.
 Copyright 2023 Joaquín Cuéllar <joaquin (dot) cuellar (at) riseup (dot) net>

 PixResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 PixResiduos is distributed in the hope that it will
 be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with PixResiduos.
 If not, see <https://www.gnu.org/licenses/>.
```
