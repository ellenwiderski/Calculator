#include "operandButton.h"
#include <iostream>
using namespace std;

OperandButton::OperandButton(int x, int y, int w, int h, char* label, int operand) : Fl_Button(x,y,w,h,label) {
  this->operand = operand;
}

int OperandButton::getOperand() {
  return this->operand;
}
