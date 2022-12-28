#ifndef LedMatrixController_h
#define LedMatrixController_h


#include "Arduino.h"

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
        void LedState(COLOR color, byte rowIndex, byte colIndex, byte value);
        void Refresh(byte refreshRate);
        void RememberState(bool flag);
        void MakeStatesMatrix();
        void UpdateStatesMatrix(byte rowIndex, byte colIndex, byte color);
        void CheckStatesMatrix();
        //void printArray();
        bool IsOn(byte rowIndex, byte colIndex);
};

#endif
