@echo off

set name="demo"

set path=%path%;..\bin\

set CC65_HOME=..\

cc65 %name%.c --add-source -g
ca65 crt0.s -g
ca65 math.s -g
ca65 %name%.s -g

ld65 -C nrom_32k_vert.cfg -o %name%.nes math.o crt0.o %name%.o nes.lib -Ln labels.txt --dbgfile %name%.dbg

del *.o

%name%.nes
