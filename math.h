#ifndef INC_08_PADS_MATH_H
#define INC_08_PADS_MATH_H

#define NUM_VIRUSES 16

typedef struct {
    unsigned char x[NUM_VIRUSES];
    unsigned char y[NUM_VIRUSES];
} VirusCoordinates;

#define VIRUS_PATH_LENGTH 256

typedef struct {
    unsigned char x[VIRUS_PATH_LENGTH];
    unsigned char y[VIRUS_PATH_LENGTH];
} VirusPath;

extern VirusPath virusPath;

#endif //INC_08_PADS_MATH_H

