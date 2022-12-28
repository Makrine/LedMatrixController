#ifndef LedMatrixController_h
#define LedMatrixController_h


#include "Arduino.h"

enum COLOR
{
    OFF,
    RED,
    GREEN,
    BLUE
};


class LedController
{
    protected:
        struct STATES
        {
            COLOR color;
            byte value;
        };

        STATES **myStates;
        byte **states;
        byte *rows, *colR, *colG, *colB;
        byte rowSize, colSize;
        byte refreshRate;

        void SetPinModes();
        void MakeStatesMatrix();
        //void UpdateStatesMatrix(byte rowIndex, byte colIndex, byte color);
        void UpdateStatesMatrix(byte rowIndex, byte colIndex, COLOR color, byte value);
        void MakeStatesMatrixSTRUCT();
        void Refresh(byte refreshRate);

    public:
        LedController(byte *r, byte *cR, byte *cG, byte *cB, byte rS, byte cS, byte rR);
        
        void ResetStates();
        void LedState(COLOR color, byte rowIndex, byte colIndex, byte value);
        void CheckStatesMatrix();
        bool IsOn(byte rowIndex, byte colIndex);
};

#endif
