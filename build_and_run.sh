#!/bin/bash

BUILD="BUILD"
NAME="Pads"
MESEN_EXE="/home/sabina/workspace/Mesen/bin/x64/Release/Mesen.exe"

cc65 -Oirs $NAME.c --add-source
ca65 crt0.s
ca65 $NAME.s -g

ld65 -C nrom_32k_vert.cfg -o $NAME.nes crt0.o $NAME.o nes.lib -Ln labels.txt

rm -f *.o
mv labels.txt $BUILD/
mv $NAME.s $BUILD/
mv $NAME.nes $BUILD/

mono $MESEN_EXE $BUILD/$NAME.nes