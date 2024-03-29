# 2024 version 0.3 

## behaviour changes
+ Not generated DI document in input movements or in deposit station

## improves
+ upgraded pvbrowser version, and using qt5 now.
+ updated cars database table, and entity with 30 associated costumers now.

## fixes
+ Using valgrind for detecting memory leaks, fixing them.
+ Fixed initialization script for linking local dynamic library. (dirty fix, but working for now)
+ Fixed some int functions returning nothing, with undefined behaviour.

## code improvement
+ Source code moved and arranged
+ Improve DI printing by moving it's code out from baseForm classes to printing ones.
+ Code cleaning, fixing functions with no return statement, etc.
+ Formulario files to baseForm renaming
+ Removed unused staff in baseForm class.
+ State machine source code splitted in several files for easy reading, fixing and improving.

# 2022/04/28 version 0.2rc1 

## improves
+ now we can configure of ticket printer.
+ ticket layout and routines implemented.
+ ticket printing implemented in incoming material input movements.

## code improvement
+ printing is going to be managed now by external classes, DI printing is not yet implemented.
+ logic saving movements is now more efficient and easy to read.
+ some log messages are not needed anymore.


# 2021/12/28 version 0.1.9dev

forked from last piResiduos production version

## improves
+ manual trafficlights control in input/output materials processes.

## fixes
+ automatic trafficlights turning on/off on input/output materials processes. Added sleep function between camera calls.


```
 This file is part of PixResiduos.

 Copyright 2021, Pixelada S. Coop. And.

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