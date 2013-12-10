#include "operatorButton.h"
using namespace std;

OperatorButton::OperatorButton(int x,int y, int w, int h, char* label, char symbol) : Fl_Button(x,y,w,h,label) {
  this->symbol = symbol;
}

char OperatorButton::getOperator() {
  return this->symbol;
}
