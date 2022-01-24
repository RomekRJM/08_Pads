#include "LIB/neslib.h"
#include "LIB/nesdoug.h"
#include "Sprites.h"
#include "lungs.h"
#include "math.h"

typedef struct {
    int x;
    int y;
} Coordinates;

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
Coordinates virusCoordinates = {20, 20};

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


// PROTOTYPES
void draw_sprites(void);

void movement(void);

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

    while (1) {
        movement();
        draw_sprites();
        ppu_wait_nmi();
//        gray_line();
    }
}

void draw_sprites() {
    oam_clear();
    oam_meta_spr(virusCoordinates.x, virusCoordinates.y, virus);
}

void movement() {
    virusCoordinates.x = 20 + 128 * sin(get_frame_count());
    virusCoordinates.y = 20 + 128 * cos(get_frame_count());
}