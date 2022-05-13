#include "lib/neslib.h"
#include "lib/nesdoug.h"
#include "sprites.h"
#include "lungs.h"
#include "math.h"

#define NUM_VIRUSES 16

#pragma bss-name(push, "ZEROPAGE")

// GLOBAL VARIABLES
Coordinates virusCoordinates[NUM_VIRUSES];
Coordinates initialVirusCoordinates[NUM_VIRUSES];
unsigned char i;


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
        0x0f, 0x3d, 0x05, 0x17,
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
        0x0f, 0x3d, 0x30, 0x05,
};

void initialise_viruses() {
    int i;
    int virusesInRow = 0;
    int y = 120;
    int x = 54;

    for (i = 0; i < NUM_VIRUSES; ++i) {
        initialVirusCoordinates[i].x = x;
        initialVirusCoordinates[i].y = y;

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

    virusCoordinates[0].x = initialVirusCoordinates[0].x + virusPath[get_frame_count()].x;
    virusCoordinates[0].y = initialVirusCoordinates[0].y + virusPath[get_frame_count()].y;

    virusCoordinates[1].x = initialVirusCoordinates[1].x + virusPath[get_frame_count()].x;
    virusCoordinates[1].y = initialVirusCoordinates[1].y + virusPath[get_frame_count()].y;

    virusCoordinates[2].x = initialVirusCoordinates[2].x + virusPath[get_frame_count()].x;
    virusCoordinates[2].y = initialVirusCoordinates[2].y + virusPath[get_frame_count()].y;

    virusCoordinates[3].x = initialVirusCoordinates[3].x + virusPath[get_frame_count()].x;
    virusCoordinates[3].y = initialVirusCoordinates[3].y + virusPath[get_frame_count()].y;

    virusCoordinates[4].x = initialVirusCoordinates[4].x + virusPath[get_frame_count()].x;
    virusCoordinates[4].y = initialVirusCoordinates[4].y + virusPath[get_frame_count()].y;

    virusCoordinates[5].x = initialVirusCoordinates[5].x + virusPath[get_frame_count()].x;
    virusCoordinates[5].y = initialVirusCoordinates[5].y + virusPath[get_frame_count()].y;

    virusCoordinates[6].x = initialVirusCoordinates[6].x + virusPath[get_frame_count()].x;
    virusCoordinates[6].y = initialVirusCoordinates[6].y + virusPath[get_frame_count()].y;

    virusCoordinates[7].x = initialVirusCoordinates[7].x + virusPath[get_frame_count()].x;
    virusCoordinates[7].y = initialVirusCoordinates[7].y + virusPath[get_frame_count()].y;

    virusCoordinates[8].x = initialVirusCoordinates[8].x + virusPath[get_frame_count()].x;
    virusCoordinates[8].y = initialVirusCoordinates[8].y + virusPath[get_frame_count()].y;

    virusCoordinates[9].x = initialVirusCoordinates[9].x + virusPath[get_frame_count()].x;
    virusCoordinates[9].y = initialVirusCoordinates[9].y + virusPath[get_frame_count()].y;

    virusCoordinates[10].x = initialVirusCoordinates[10].x + virusPath[get_frame_count()].x;
    virusCoordinates[10].y = initialVirusCoordinates[10].y + virusPath[get_frame_count()].y;

    virusCoordinates[11].x = initialVirusCoordinates[11].x + virusPath[get_frame_count()].x;
    virusCoordinates[11].y = initialVirusCoordinates[11].y + virusPath[get_frame_count()].y;

    virusCoordinates[12].x = initialVirusCoordinates[12].x + virusPath[get_frame_count()].x;
    virusCoordinates[12].y = initialVirusCoordinates[12].y + virusPath[get_frame_count()].y;

    virusCoordinates[13].x = initialVirusCoordinates[13].x + virusPath[get_frame_count()].x;
    virusCoordinates[13].y = initialVirusCoordinates[13].y + virusPath[get_frame_count()].y;

    virusCoordinates[14].x = initialVirusCoordinates[14].x + virusPath[get_frame_count()].x;
    virusCoordinates[14].y = initialVirusCoordinates[14].y + virusPath[get_frame_count()].y;

    virusCoordinates[15].x = initialVirusCoordinates[15].x + virusPath[get_frame_count()].x;
    virusCoordinates[15].y = initialVirusCoordinates[15].y + virusPath[get_frame_count()].y;
}

void draw_sprites() {
    static int virusSprite = 0;
    int i;
    oam_clear();

    if (get_frame_count() % 8 == 0) {
        virusSprite = ++virusSprite % 4;
    }

    for (i = 0; i < NUM_VIRUSES; ++i) {
        switch (virusSprite) {
            case 0:
                oam_meta_spr(virusCoordinates[i].x, virusCoordinates[i].y, virusSprite0);
                break;
            case 1:
                oam_meta_spr(virusCoordinates[i].x, virusCoordinates[i].y, virusSprite1);
                break;
            case 2:
                oam_meta_spr(virusCoordinates[i].x, virusCoordinates[i].y, virusSprite2);
                break;
            case 3:
                oam_meta_spr(virusCoordinates[i].x, virusCoordinates[i].y, virusSprite3);
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
