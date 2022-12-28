#ifndef LedMatrixController_h
#define LedMatrixController_h


#include "Arduino.h"

class LedController
{
    protected:
        byte *rows, *colR, *colG, *colB;
        byte rowSize, colSize;
        byte refreshRate;

    public:
        enum COLOR
        {
            RED,
            GREEN,
            BLUE
        };
        LedController(byte *r, byte *cR, byte *cG, byte *cB, byte rS, byte cS, byte rR);
        void SetPinModes();
        void ResetStates();
        void LedState(COLOR color, byte rowIndex, byte colIndex, byte value);
        void Refresh(byte refreshRate);
};

#endif
