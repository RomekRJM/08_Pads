#include "lib/neslib.h"
#include "lib/nesdoug.h"
#include "sprites.h"
#include "lungs.h"
#include "math.h"

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
VirusCoordinates virusCoordinates;
VirusCoordinates initialVirusCoordinates;

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
    unsigned char i;
    unsigned char virusesInRow = 0;
    unsigned char y = 120;
    unsigned char x = 54;

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
    unsigned char i;

    for (i = 0; i < NUM_VIRUSES; ++i) {
        virusCoordinates.x[i] = initialVirusCoordinates.x[i] + virusPath.x[get_frame_count()];
        virusCoordinates.y[i] = initialVirusCoordinates.y[i] + virusPath.y[get_frame_count()];
    }
}

void draw_sprites() {
    static unsigned char virusSprite = 0;
    unsigned char i;
    oam_clear();

    if ((get_frame_count() & 7) == 0) {
        virusSprite = ++virusSprite & 3;
    }

    for (i = 0; i < NUM_VIRUSES; ++i) {
        switch (virusSprite) {
            case 0:
                oam_meta_spr(virusCoordinates.x[i], virusCoordinates.y[i], virusSprite0);
                break;
            case 1:
                oam_meta_spr(virusCoordinates.x[i], virusCoordinates.y[i], virusSprite1);
                break;
            case 2:
                oam_meta_spr(virusCoordinates.x[i], virusCoordinates.y[i], virusSprite2);
                break;
            case 3:
                oam_meta_spr(virusCoordinates.x[i], virusCoordinates.y[i], virusSprite3);
                break;
        }
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
