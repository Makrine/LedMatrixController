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
      //UpdateStatesMatrix(rowIndex, colIndex, 0);
      UpdateStatesMatrix(rowIndex, colIndex, OFF, 0);
    }
      
    else
    {
      digitalWrite(rows[rowIndex], LOW);
      switch(color)
      {
          case COLOR::RED:
              analogWrite(colR[colIndex], value);
              //UpdateStatesMatrix(rowIndex, colIndex, red);
              UpdateStatesMatrix(rowIndex, colIndex, RED, value);
              break;
          case COLOR::GREEN:
              analogWrite(colG[colIndex], value);
              //UpdateStatesMatrix(rowIndex, colIndex, green);
              UpdateStatesMatrix(rowIndex, colIndex, GREEN, value);
              break;
          case COLOR::BLUE:
              analogWrite(colB[colIndex], value);
              //UpdateStatesMatrix(rowIndex, colIndex, blue);
              UpdateStatesMatrix(rowIndex, colIndex, BLUE, value);
              break;
          default:
              //UpdateStatesMatrix(rowIndex, colIndex, off);
              UpdateStatesMatrix(rowIndex, colIndex, OFF, value);
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

void LedController::MakeStatesMatrix()
{
  states = new byte*[rowSize];
  for(int i = 0; i < rowSize; i++)
  {
      states[i] = new byte[colSize]{0};
  }
}

void LedController::MakeStatesMatrixSTRUCT()
{
  myStates = new STATES*[rowSize];
  STATES s;
  s.color = OFF;
  s.value = 0;  
  for(int i = 0; i < rowSize; i++)
  {
      myStates[i] = new STATES[colSize]{s};
  }
}


// void LedController::UpdateStatesMatrix(byte rowIndex, byte colIndex, byte color)
// {
//   states[rowIndex][colIndex] = color;
// }

void LedController::UpdateStatesMatrix(byte rowIndex, byte colIndex, COLOR color, byte value)
{
  myStates[rowIndex][colIndex].color = color;
  myStates[rowIndex][colIndex].value = value;
}


// void LedController::CheckStatesMatrix()
// {
//   for(int i = 0; i < rowSize; i++)
//   {
//     for(int j = 0; j < colSize; j++)
//     {
//       if(states[i][j] == off)
//         LedState(GREEN, i, j, 0);
//       if(states[i][j] == green)
//         LedState(GREEN, i, j, 255);
//       else if(states[i][j] == red)
//         LedState(RED, i, j, 255);
//       else if(states[i][j] == blue)
//         LedState(BLUE, i, j, 255);
//     }
//   }
// }

void LedController::CheckStatesMatrix()
{
  for(int i = 0; i < rowSize; i++)
    for(int j = 0; j < colSize; j++)
      LedState(myStates[i][j].color, i, j, myStates[i][j].value);
}

bool LedController::IsOn(byte rowIndex, byte colIndex)
{
  if(states[rowIndex][colIndex] != off) return true;
  else return false;
}


#endif