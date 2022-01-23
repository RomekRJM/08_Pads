@echo off

set name="Pads"

set path=%path%;..\bin\

set CC65_HOME=..\

cc65 -Oirs math.c --add-source
cc65 -Oirs %name%.c --add-source
ca65 crt0.s
ca65 math.s
ca65 %name%.s -g

ld65 -C nrom_32k_vert.cfg -o %name%.nes crt0.o %name%.o math.o nes.lib -Ln labels.txt

del *.o

move /Y labels.txt BUILD\ 
move /Y %name%.s BUILD\ 
move /Y %name%.nes BUILD\ 


BUILD\%name%.nes
