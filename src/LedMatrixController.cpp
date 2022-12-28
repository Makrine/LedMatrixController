#ifndef LedMatrixController
#define LedMatrixController

#include "LedMatrixController.h"

LedController::LedController(byte *r, byte *cR, byte *cG, byte *cB, byte rS, byte cS, byte rR)
{
    rows = r;
    colR = cR;
    colG = cG;
    colB = cB;
    refreshRate = rR;

    rowSize = rS;
    colSize = cS;

    SetPinModes();
}

void LedController::SetPinModes()
{
    for(byte i = 0; i < rowSize; i++)
        pinMode(rows[i], OUTPUT);
    for(byte i = 0; i < colSize; i++)
    {
        pinMode(colR[i], OUTPUT);
        pinMode(colG[i], OUTPUT);
        pinMode(colB[i], OUTPUT);
    } 
}

void LedController::ResetStates()
{
    for(byte i = 0; i < rowSize; i++)
        digitalWrite(rows[i], HIGH);
    for(byte i = 0; i < colSize; i++)
    {
        analogWrite(colR[i], 0);
        analogWrite(colG[i], 0);
        analogWrite(colB[i], 0);
    } 
}

void LedController::LedState(COLOR color, byte rowIndex, byte colIndex, byte value)
{
    if(value == 0)
    {
      digitalWrite(rows[rowIndex], HIGH);
    }
      
    else
      digitalWrite(rows[rowIndex], LOW);
    switch(color)
    {
        case COLOR::RED:
            analogWrite(colR[colIndex], value);
            break;
        case COLOR::GREEN:
            analogWrite(colG[colIndex], value);
            break;
        case COLOR::BLUE:
            analogWrite(colB[colIndex], value);
            break;
    }
    Refresh(refreshRate);
}

void LedController::Refresh(byte refreshRate)
{
  delay(refreshRate);
  ResetStates();
}

#endif