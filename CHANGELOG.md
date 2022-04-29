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