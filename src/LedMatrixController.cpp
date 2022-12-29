#ifndef LedMatrixController
#define LedMatrixController

#include "LedMatrixController.h"

byte off = 0;
byte green = 1;
byte red = 2;
byte blue = 3;


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
    ResetStates();
    MakeStatesMatrix();
}

void LedController::MakeStatesMatrix()
{
  states = new byte*[rowSize];
  for(int i = 0; i < rowSize; i++)
  {
      states[i] = new byte[colSize]{0};
  }
}

void LedController::CheckStatesMatrix()
{
  for(int i = 0; i < rowSize; i++)
  {
    for(int j = 0; j < colSize; j++)
    {
      INDEX_LED index(i, j);
      if(states[i][j] == off)
        LedState(GREEN, index, 0);
      if(states[i][j] == green)
        LedState(GREEN, index, 255);
      else if(states[i][j] == red)
        LedState(RED, index, 255);
      else if(states[i][j] == blue)
        LedState(BLUE, index, 255);
    }
  }
}

byte** LedController::GetStatesMatrix()
{
	return states;
}

void LedController::UpdateStatesMatrix(INDEX_LED index, byte color)
{
  states[index.row][index.column] = color;
}

bool LedController::IsOn(INDEX_LED index)
{
  if(states[index.row][index.column]  != off) return true;
  else return false;
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

void LedController::LedState(COLOR color, INDEX_LED index, byte value)
{
    if(value == 0)
    {
      digitalWrite(rows[index.row], HIGH);
      UpdateStatesMatrix(index, 0);
    }
      
    else
    {
      digitalWrite(rows[index.row], LOW);
      switch(color)
      {
          case COLOR::RED:
              analogWrite(colR[index.column], value);
              UpdateStatesMatrix(index, red);
              break;
          case COLOR::GREEN:
              analogWrite(colG[index.column], value);
              UpdateStatesMatrix(index, green);
              break;
          case COLOR::BLUE:
              analogWrite(colB[index.column], value);
              UpdateStatesMatrix(index, blue);
              break;
      }
      
    }
    
    Refresh(refreshRate);

}


void LedController::Refresh(byte refreshRate)
{
  delay(refreshRate);
  ResetStates();
}

#endif
