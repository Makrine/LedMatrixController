#ifndef LedMatrixController_h
#define LedMatrixController_h


#include "Arduino.h"

struct INDEX_LED
{
    int row, column;

    INDEX_LED()
    {
        row = -1;
        column = -1;
    }
    INDEX_LED(int r, int c)
    {
        row = r;
        column = c;
    }
};

class LedController
{
    protected:
        byte **states;
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
        void LedState(COLOR color, INDEX_LED index, byte value);
        void Refresh(byte refreshRate);
        void MakeStatesMatrix();
        void UpdateStatesMatrix(INDEX_LED index, byte color);
        void CheckStatesMatrix();
        bool IsOn(INDEX_LED index);
        byte** GetStatesMatrix();
};

#endif
