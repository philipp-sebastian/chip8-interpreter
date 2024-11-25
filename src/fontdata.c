//
// Created by Sebastian on 25.11.24.
//

#include "../include/common.h"

unsigned char* initializeFont(void)
{
    unsigned char* fontData = (unsigned char*)malloc(AMOUNT_OF_SPRITES * FONT_HEIGHT * sizeof(char));
    if (fontData == NULL)
    {
        SDL_Log("Error allocating memory for fontData");
        return NULL;
    }

    // A
    fontData[fA*FONT_HEIGHT + 0] = 0x70;
    fontData[fA*FONT_HEIGHT + 1] = 0xD8;
    fontData[fA*FONT_HEIGHT + 2] = 0x88;
    fontData[fA*FONT_HEIGHT + 3] = 0x88;
    fontData[fA*FONT_HEIGHT + 4] = 0xF8;
    fontData[fA*FONT_HEIGHT + 5] = 0x88;
    fontData[fA*FONT_HEIGHT + 6] = 0x88;

// M
    fontData[fM*FONT_HEIGHT + 0] = 0xF8;
    fontData[fM*FONT_HEIGHT + 1] = 0xF8;
    fontData[fM*FONT_HEIGHT + 2] = 0xA8;
    fontData[fM*FONT_HEIGHT + 3] = 0xA8;
    fontData[fM*FONT_HEIGHT + 4] = 0xA8;
    fontData[fM*FONT_HEIGHT + 5] = 0xA8;
    fontData[fM*FONT_HEIGHT + 6] = 0xA8;

// G
    fontData[fG*FONT_HEIGHT + 0] = 0xF8;
    fontData[fG*FONT_HEIGHT + 1] = 0x80;
    fontData[fG*FONT_HEIGHT + 2] = 0x80;
    fontData[fG*FONT_HEIGHT + 3] = 0xB8;
    fontData[fG*FONT_HEIGHT + 4] = 0x88;
    fontData[fG*FONT_HEIGHT + 5] = 0x88;
    fontData[fG*FONT_HEIGHT + 6] = 0xF8;

// E
    fontData[fE*FONT_HEIGHT + 0] = 0xF8;
    fontData[fE*FONT_HEIGHT + 1] = 0x80;
    fontData[fE*FONT_HEIGHT + 2] = 0x80;
    fontData[fE*FONT_HEIGHT + 3] = 0xF8;
    fontData[fE*FONT_HEIGHT + 4] = 0x80;
    fontData[fE*FONT_HEIGHT + 5] = 0x80;
    fontData[fE*FONT_HEIGHT + 6] = 0xF8;

// O
    fontData[fO*FONT_HEIGHT + 0] = 0xF8;
    fontData[fO*FONT_HEIGHT + 1] = 0x88;
    fontData[fO*FONT_HEIGHT + 2] = 0x88;
    fontData[fO*FONT_HEIGHT + 3] = 0x88;
    fontData[fO*FONT_HEIGHT + 4] = 0x88;
    fontData[fO*FONT_HEIGHT + 5] = 0x88;
    fontData[fO*FONT_HEIGHT + 6] = 0xF8;

// V
    fontData[fV*FONT_HEIGHT + 0] = 0x88;
    fontData[fV*FONT_HEIGHT + 1] = 0x88;
    fontData[fV*FONT_HEIGHT + 2] = 0x88;
    fontData[fV*FONT_HEIGHT + 3] = 0x88;
    fontData[fV*FONT_HEIGHT + 4] = 0x88;
    fontData[fV*FONT_HEIGHT + 5] = 0x50;
    fontData[fV*FONT_HEIGHT + 6] = 0x20;

// R
    fontData[fR*FONT_HEIGHT + 0] = 0xF8;
    fontData[fR*FONT_HEIGHT + 1] = 0x88;
    fontData[fR*FONT_HEIGHT + 2] = 0x88;
    fontData[fR*FONT_HEIGHT + 3] = 0xF8;
    fontData[fR*FONT_HEIGHT + 4] = 0xE0;
    fontData[fR*FONT_HEIGHT + 5] = 0xB0;
    fontData[fR*FONT_HEIGHT + 6] = 0x98;

// P
    fontData[fP*FONT_HEIGHT + 0] = 0xF8;
    fontData[fP*FONT_HEIGHT + 1] = 0x88;
    fontData[fP*FONT_HEIGHT + 2] = 0x88;
    fontData[fP*FONT_HEIGHT + 3] = 0xF8;
    fontData[fP*FONT_HEIGHT + 4] = 0x80;
    fontData[fP*FONT_HEIGHT + 5] = 0x80;
    fontData[fP*FONT_HEIGHT + 6] = 0x80;

// S
    fontData[fS*FONT_HEIGHT + 0] = 0xF8;
    fontData[fS*FONT_HEIGHT + 1] = 0x80;
    fontData[fS*FONT_HEIGHT + 2] = 0x80;
    fontData[fS*FONT_HEIGHT + 3] = 0xF8;
    fontData[fS*FONT_HEIGHT + 4] = 0x08;
    fontData[fS*FONT_HEIGHT + 5] = 0x08;
    fontData[fS*FONT_HEIGHT + 6] = 0xF8;

// T
    fontData[fT*FONT_HEIGHT + 0] = 0xF8;
    fontData[fT*FONT_HEIGHT + 1] = 0x20;
    fontData[fT*FONT_HEIGHT + 2] = 0x20;
    fontData[fT*FONT_HEIGHT + 3] = 0x20;
    fontData[fT*FONT_HEIGHT + 4] = 0x20;
    fontData[fT*FONT_HEIGHT + 5] = 0x20;
    fontData[fT*FONT_HEIGHT + 6] = 0x20;

// 0 (same as O)
    fontData[f0*FONT_HEIGHT + 0] = 0xF8;
    fontData[f0*FONT_HEIGHT + 1] = 0x88;
    fontData[f0*FONT_HEIGHT + 2] = 0x88;
    fontData[f0*FONT_HEIGHT + 3] = 0x88;
    fontData[f0*FONT_HEIGHT + 4] = 0x88;
    fontData[f0*FONT_HEIGHT + 5] = 0x88;
    fontData[f0*FONT_HEIGHT + 6] = 0xF8;

    // 1
    fontData[f1*FONT_HEIGHT + 0] = 0x08;
    fontData[f1*FONT_HEIGHT + 1] = 0x08;
    fontData[f1*FONT_HEIGHT + 2] = 0x08;
    fontData[f1*FONT_HEIGHT + 3] = 0x08;
    fontData[f1*FONT_HEIGHT + 4] = 0x08;
    fontData[f1*FONT_HEIGHT + 5] = 0x08;
    fontData[f1*FONT_HEIGHT + 6] = 0x08;

// 2
    fontData[f2*FONT_HEIGHT + 0] = 0xF8;
    fontData[f2*FONT_HEIGHT + 1] = 0x08;
    fontData[f2*FONT_HEIGHT + 2] = 0x08;
    fontData[f2*FONT_HEIGHT + 3] = 0xF8;
    fontData[f2*FONT_HEIGHT + 4] = 0x80;
    fontData[f2*FONT_HEIGHT + 5] = 0x80;
    fontData[f2*FONT_HEIGHT + 6] = 0xF8;

// 3
    fontData[f3*FONT_HEIGHT + 0] = 0xF8;
    fontData[f3*FONT_HEIGHT + 1] = 0x08;
    fontData[f3*FONT_HEIGHT + 2] = 0x08;
    fontData[f3*FONT_HEIGHT + 3] = 0xF8;
    fontData[f3*FONT_HEIGHT + 4] = 0x08;
    fontData[f3*FONT_HEIGHT + 5] = 0x08;
    fontData[f3*FONT_HEIGHT + 6] = 0xF8;

// 4
    fontData[f4*FONT_HEIGHT + 0] = 0x88;
    fontData[f4*FONT_HEIGHT + 1] = 0x88;
    fontData[f4*FONT_HEIGHT + 2] = 0x88;
    fontData[f4*FONT_HEIGHT + 3] = 0xF8;
    fontData[f4*FONT_HEIGHT + 4] = 0x08;
    fontData[f4*FONT_HEIGHT + 5] = 0x08;
    fontData[f4*FONT_HEIGHT + 6] = 0x08;

// 5 (same as S)
    fontData[f5*FONT_HEIGHT + 0] = 0xF8;
    fontData[f5*FONT_HEIGHT + 1] = 0x80;
    fontData[f5*FONT_HEIGHT + 2] = 0x80;
    fontData[f5*FONT_HEIGHT + 3] = 0xF8;
    fontData[f5*FONT_HEIGHT + 4] = 0x08;
    fontData[f5*FONT_HEIGHT + 5] = 0x08;
    fontData[f5*FONT_HEIGHT + 6] = 0xF8;

// 6
    fontData[f6*FONT_HEIGHT + 0] = 0x80;
    fontData[f6*FONT_HEIGHT + 1] = 0x80;
    fontData[f6*FONT_HEIGHT + 2] = 0x80;
    fontData[f6*FONT_HEIGHT + 3] = 0xF8;
    fontData[f6*FONT_HEIGHT + 4] = 0x88;
    fontData[f6*FONT_HEIGHT + 5] = 0x88;
    fontData[f6*FONT_HEIGHT + 6] = 0x88;

// 7
    fontData[f7*FONT_HEIGHT + 0] = 0xF8;
    fontData[f7*FONT_HEIGHT + 1] = 0x08;
    fontData[f7*FONT_HEIGHT + 2] = 0x18;
    fontData[f7*FONT_HEIGHT + 3] = 0x30;
    fontData[f7*FONT_HEIGHT + 4] = 0x60;
    fontData[f7*FONT_HEIGHT + 5] = 0xC0;
    fontData[f7*FONT_HEIGHT + 6] = 0x80;

// 8
    fontData[f8*FONT_HEIGHT + 0] = 0xF8;
    fontData[f8*FONT_HEIGHT + 1] = 0x88;
    fontData[f8*FONT_HEIGHT + 2] = 0x88;
    fontData[f8*FONT_HEIGHT + 3] = 0xF8;
    fontData[f8*FONT_HEIGHT + 4] = 0x88;
    fontData[f8*FONT_HEIGHT + 5] = 0x88;
    fontData[f8*FONT_HEIGHT + 6] = 0xF8;

// 9
    fontData[f9*FONT_HEIGHT + 0] = 0xF8;
    fontData[f9*FONT_HEIGHT + 1] = 0x88;
    fontData[f9*FONT_HEIGHT + 2] = 0x88;
    fontData[f9*FONT_HEIGHT + 3] = 0xF8;
    fontData[f9*FONT_HEIGHT + 4] = 0x08;
    fontData[f9*FONT_HEIGHT + 5] = 0x08;
    fontData[f9*FONT_HEIGHT + 6] = 0xF8;

// L
    fontData[fL*FONT_HEIGHT + 0] = 0x80;
    fontData[fL*FONT_HEIGHT + 1] = 0x80;
    fontData[fL*FONT_HEIGHT + 2] = 0x80;
    fontData[fL*FONT_HEIGHT + 3] = 0x80;
    fontData[fL*FONT_HEIGHT + 4] = 0x80;
    fontData[fL*FONT_HEIGHT + 5] = 0x80;
    fontData[fL*FONT_HEIGHT + 6] = 0xF8;

// C
    fontData[fC*FONT_HEIGHT + 0] = 0xF8;
    fontData[fC*FONT_HEIGHT + 1] = 0x80;
    fontData[fC*FONT_HEIGHT + 2] = 0x80;
    fontData[fC*FONT_HEIGHT + 3] = 0x80;
    fontData[fC*FONT_HEIGHT + 4] = 0x80;
    fontData[fC*FONT_HEIGHT + 5] = 0x80;
    fontData[fC*FONT_HEIGHT + 6] = 0xF8;

// X
    fontData[fX*FONT_HEIGHT + 0] = 0x88;
    fontData[fX*FONT_HEIGHT + 1] = 0xD8;
    fontData[fX*FONT_HEIGHT + 2] = 0x70;
    fontData[fX*FONT_HEIGHT + 3] = 0x20;
    fontData[fX*FONT_HEIGHT + 4] = 0x70;
    fontData[fX*FONT_HEIGHT + 5] = 0xD8;
    fontData[fX*FONT_HEIGHT + 6] = 0x88;

// N
    fontData[fN*FONT_HEIGHT + 0] = 0xC8;
    fontData[fN*FONT_HEIGHT + 1] = 0xC8;
    fontData[fN*FONT_HEIGHT + 2] = 0xE8;
    fontData[fN*FONT_HEIGHT + 3] = 0xA8;
    fontData[fN*FONT_HEIGHT + 4] = 0xB8;
    fontData[fN*FONT_HEIGHT + 5] = 0x98;
    fontData[fN*FONT_HEIGHT + 6] = 0x88;

// I
    fontData[fI*FONT_HEIGHT + 0] = 0x20;
    fontData[fI*FONT_HEIGHT + 1] = 0x20;
    fontData[fI*FONT_HEIGHT + 2] = 0x20;
    fontData[fI*FONT_HEIGHT + 3] = 0x20;
    fontData[fI*FONT_HEIGHT + 4] = 0x20;
    fontData[fI*FONT_HEIGHT + 5] = 0x20;
    fontData[fI*FONT_HEIGHT + 6] = 0x20;

// Dot
    fontData[fDOT*FONT_HEIGHT + 0] = 0x00;
    fontData[fDOT*FONT_HEIGHT + 1] = 0x00;
    fontData[fDOT*FONT_HEIGHT + 2] = 0x70;
    fontData[fDOT*FONT_HEIGHT + 3] = 0x70;
    fontData[fDOT*FONT_HEIGHT + 4] = 0x70;
    fontData[fDOT*FONT_HEIGHT + 5] = 0x00;
    fontData[fDOT*FONT_HEIGHT + 6] = 0x00;

    //	B
    //	•	D
    //	•	F
    //	•	H
    //	•	J
    //	•	K
    //	•	Q
    //	•	U
    //	•	W
    //	•	Y
    //	•	Z

    return fontData;
}

