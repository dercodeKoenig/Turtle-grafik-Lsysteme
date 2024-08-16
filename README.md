School project:
Create a program that reads turtle drawing instructions from a txt file and draws it on screen.

Optional feature implemented:
Add support for L-systems

There is a build for windows and linux.
Example input.txt files are in the source code folders

example file explained

Line 1:
900x900x1x0 
(screen resolution, line width, and I forgot the last one)

Following lines:
r90
F
(turtle instructions)

#def
F:FF[//F*F*F][*F/F/F]
#end
(define how one instruction should change every iterations)

#al
F:f10
*:r30
/:r-30
#end
(define what an instruction should be translated to when done with L-system parsing)

#rek
5
(define how often L-system parsing should run)
