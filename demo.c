#include "lib/neslib.h"
#include "lib/nesdoug.h"
#include "sprites.h"
#include "lungs.h"
#include "math.h"

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
VirusCoordinates virusCoordinates;
VirusCoordinates initialVirusCoordinates;
unsigned char virusSprite = 0;
unsigned char virusesInRow = 0;
unsigned char y = 120;
unsigned char x = 54;
unsigned char i;
unsigned char initial;
unsigned char path;
const unsigned char *sprite;

#pragma bss-name(push, "BSS")

volatile unsigned char *dbg1 = (volatile unsigned char *) 0x80;
volatile unsigned char *dbg2 = (volatile unsigned char *) 0x81;
volatile unsigned char *dbg3 = (volatile unsigned char *) 0x82;

const char paletteBackground[] = {
        0x0f, 0x06, 0x16, 0x26,
        0x0f, 0x06, 0x16, 0x26,
        0x0f, 0x06, 0x16, 0x26,
        0x0f, 0x06, 0x16, 0x26,
};

const char paletteSprite[] = {
        0x0f, 0x3d, 0x05, 0x17,
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
};

void initialise_viruses() {
    for (i = 0; i < NUM_VIRUSES; ++i) {
        initialVirusCoordinates.x[i] = x;
        initialVirusCoordinates.y[i] = y;

        if (virusesInRow < 3) {
            x += 40;
            ++virusesInRow;
        } else {
            x = 54;
            y += 20;
            virusesInRow = 0;
        }
    }
}

void movement() {
    for (i = 0; i < NUM_VIRUSES; ++i) {
        path = virusPath.x[get_frame_count()];
        initial = initialVirusCoordinates.x[i];
        virusCoordinates.x[i] = initial + path;

        path = virusPath.y[get_frame_count()];
        initial = initialVirusCoordinates.y[i];
        virusCoordinates.y[i] = initial + path;
    }
}

void draw_sprites() {
    oam_clear();

    if ((get_frame_count() & 7) == 0) {
        virusSprite = ++virusSprite & 3;
    }

    sprite = virusSpriteLookup[virusSprite];

    for (i = 0; i < NUM_VIRUSES; ++i) {
        oam_meta_spr(virusCoordinates.x[i], virusCoordinates.y[i], sprite);
    }
}

void init_nes() {
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
}

void main(void) {
    init_nes();

    initialise_viruses();

    while (1) {
        movement();
        draw_sprites();
//        gray_line();
        ppu_wait_nmi();
    }
}
