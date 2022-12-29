#include "LedMatrixController.h"

byte refreshRate = 1;

byte rows[3] = {7, 6, 5};
byte colsR[3] = {11, 10, 9};
byte colsB[3] = {A3, A4, A5};
byte colsG[3] = {A0, A1, A2};

LedController ledController(rows, colsR, colsB, colsG, 3, 3, refreshRate);

void setup() {}

void loop()
{
  ledController.LedState(ledController.BLUE, 1, 0, 255);
  ledController.LedState(ledController.RED, 0, 0, 255);
  ledController.LedState(ledController.GREEN, 2, 0, 255);

  ledController.LedState(ledController.GREEN, 2, 2, 255);
  ledController.LedState(ledController.BLUE, 2, 2, 255);
  ledController.LedState(ledController.RED, 2, 2, 255);
}
