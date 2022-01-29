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
    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[0];
    virusCoordinates.x[0] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[0];
    virusCoordinates.y[0] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[1];
    virusCoordinates.x[1] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[1];
    virusCoordinates.y[1] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[2];
    virusCoordinates.x[2] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[2];
    virusCoordinates.y[2] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[3];
    virusCoordinates.x[3] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[3];
    virusCoordinates.y[3] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[4];
    virusCoordinates.x[4] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[4];
    virusCoordinates.y[4] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[5];
    virusCoordinates.x[5] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[5];
    virusCoordinates.y[5] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[6];
    virusCoordinates.x[6] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[6];
    virusCoordinates.y[6] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[7];
    virusCoordinates.x[7] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[7];
    virusCoordinates.y[7] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[8];
    virusCoordinates.x[8] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[8];
    virusCoordinates.y[8] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[9];
    virusCoordinates.x[9] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[9];
    virusCoordinates.y[9] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[10];
    virusCoordinates.x[10] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[10];
    virusCoordinates.y[10] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[11];
    virusCoordinates.x[11] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[11];
    virusCoordinates.y[11] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[12];
    virusCoordinates.x[12] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[12];
    virusCoordinates.y[12] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[13];
    virusCoordinates.x[13] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[13];
    virusCoordinates.y[13] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[14];
    virusCoordinates.x[14] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[14];
    virusCoordinates.y[14] = initial + path;

    path = virusPath.x[get_frame_count()];
    initial = initialVirusCoordinates.x[15];
    virusCoordinates.x[15] = initial + path;

    path = virusPath.y[get_frame_count()];
    initial = initialVirusCoordinates.y[15];
    virusCoordinates.y[15] = initial + path;
}

void draw_sprites() {
    oam_clear();

    if ((get_frame_count() & 7) == 0) {
        virusSprite = ++virusSprite & 3;
    }

    sprite = virusSpriteLookup[virusSprite];

    oam_meta_spr(virusCoordinates.x[0], virusCoordinates.y[0], sprite);
    oam_meta_spr(virusCoordinates.x[1], virusCoordinates.y[1], sprite);
    oam_meta_spr(virusCoordinates.x[2], virusCoordinates.y[2], sprite);
    oam_meta_spr(virusCoordinates.x[3], virusCoordinates.y[3], sprite);
    oam_meta_spr(virusCoordinates.x[4], virusCoordinates.y[4], sprite);
    oam_meta_spr(virusCoordinates.x[5], virusCoordinates.y[5], sprite);
    oam_meta_spr(virusCoordinates.x[6], virusCoordinates.y[6], sprite);
    oam_meta_spr(virusCoordinates.x[7], virusCoordinates.y[7], sprite);
    oam_meta_spr(virusCoordinates.x[8], virusCoordinates.y[8], sprite);
    oam_meta_spr(virusCoordinates.x[9], virusCoordinates.y[9], sprite);
    oam_meta_spr(virusCoordinates.x[10], virusCoordinates.y[10], sprite);
    oam_meta_spr(virusCoordinates.x[11], virusCoordinates.y[11], sprite);
    oam_meta_spr(virusCoordinates.x[12], virusCoordinates.y[12], sprite);
    oam_meta_spr(virusCoordinates.x[13], virusCoordinates.y[13], sprite);
    oam_meta_spr(virusCoordinates.x[14], virusCoordinates.y[14], sprite);
    oam_meta_spr(virusCoordinates.x[15], virusCoordinates.y[15], sprite);

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
