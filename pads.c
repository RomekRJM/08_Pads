#include "lib/neslib.h"
#include "lib/nesdoug.h"
#include "sprites.h"
#include "lungs.h"
#include "math.h"

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES


#pragma bss-name(push, "BSS")

volatile unsigned int *dbg1 = (volatile unsigned int *) 0x80;
volatile unsigned int *dbg2 = (volatile unsigned int *) 0x81;
volatile unsigned char *dbg3 = (volatile unsigned char *) 0x82;

const char paletteBackground[] = {
        0x0f, 0x06, 0x16, 0x26,
        0x0f, 0x06, 0x16, 0x26,
        0x0f, 0x06, 0x16, 0x26,
        0x0f, 0x06, 0x16, 0x26,
};

const char paletteSprite[] = {
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
};

Coordinates zeroCoordinates = {0, 0};
Coordinates fortyCoordinates = { 40, 40};
Coordinates *virusCoordinates;
Coordinates *initialVirusCoordinates;

// PROTOTYPES
void draw_sprites(Coordinates *virusCoordinates, const unsigned char *virusSprite) {
    oam_clear();
    oam_meta_spr(virusCoordinates->x, virusCoordinates->y, virusSprite);
}

void movement(Coordinates *virusCoordinates, Coordinates *initialVirusCoordinates, const Coordinates *virusPath) {
    virusCoordinates->x = initialVirusCoordinates->x + virusPath[get_frame_count()].x;
    virusCoordinates->y = initialVirusCoordinates->y + virusPath[get_frame_count()].y;
}



void main(void) {

    ppu_off(); // screen off

    // load the palettes
    pal_bg(paletteBackground);
    pal_spr(paletteSprite);

    // use the second set of tiles for sprites
    // both bg and sprites are set to 0 by default
    bank_spr(1);

    vram_adr(NAMETABLE_A);
    // load the text
    vram_unrle(lungs);

    // turn on screen
    ppu_on_all();
    virusCoordinates = &zeroCoordinates;
    initialVirusCoordinates = &fortyCoordinates;


    while (1) {
        movement(virusCoordinates, initialVirusCoordinates, virusPath);
        draw_sprites(virusCoordinates, virus0);
        ppu_wait_nmi();
//        gray_line();
    }
}
