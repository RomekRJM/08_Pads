@echo off

set name="Pads"

set path=%path%;..\bin\

set CC65_HOME=..\

cc65 -Oirs math.c --add-source -g
cc65 -Oirs %name%.c --add-source -g
ca65 crt0.s -g
ca65 math.s -g
ca65 %name%.s -g

ld65 -C nrom_32k_vert.cfg -o %name%.nes crt0.o %name%.o math.o nes.lib -Ln labels.txt --dbgfile %name%.dbg

del *.o

move /Y labels.txt BUILD\ 
move /Y %name%.s BUILD\ 
move /Y %name%.nes BUILD\
move /Y %name%.dbg BUILD\


BUILD\%name%.nes
