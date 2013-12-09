#include <cstdlib>
#include <cstdio>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <string>
#include "operandButton.h"
#include "operatorButton.h"
using namespace std;

//Global Variables:
Fl_Box *number;
vector<OperandButton*> operandButtons;
vector<OperatorButton*> operatorButtons;
vector<const char*> stack;

//Callbacks:

void numbercb(Fl_Widget * w, void *) {
  OperandButton *num = (OperandButton *)w;
  stack.push_back(to_string(num->getOperand()).c_str());
  number->copy_label(to_string(num->getOperand()).c_str());
}

void functioncb(Fl_Widget * w, void *) {
  OperatorButton *op = (OperatorButton *)w;
  stack.push_back(op->getOperator());
  number->copy_label(op->getOperator());
}

//Main:
int main(int argc, char* argv[]) {
  Fl_Window *window = new Fl_Window(500,600);
  
  Fl_Box *screen = new Fl_Box(20,20,460,100,"");
  screen->box(FL_EMBOSSED_BOX);
  number = new Fl_Box(370,20,100,100,"");
  number->labelsize(48);
  // Purple!
  Fl_Color c = fl_rgb_color(240, 208, 255);
  screen->color(c);


  //Make the number buttons!
  vector<int> x = {20,20,140,260,20,140,260,20,140,260};
  vector<int> y = {508,416,416,416,324,324,324,232,232,232};
  c = fl_rgb_color(73,7,90);

  for (int i = 0; i < 10; i++) {
    if (i == 0) {
      OperandButton *num = new OperandButton(x[i],y[i],220,68,"",i);
      operandButtons.push_back(num);
    }
    else{
      OperandButton *num = new OperandButton(x[i],y[i],100,68,"",i);
      operandButtons.push_back(num);
    }
  }

  //Give those beautiful number buttons some labels & color
  int pos = 0;
  for (auto i : operandButtons) {
    i->copy_label(to_string(pos).c_str());
    i->color(c);
    i->labelcolor(FL_WHITE);
    i->labelsize(24);
    pos++;
  }
  
  x.clear();
  y.clear();

  //Let's set their callbacks!
  for (auto i :operandButtons) {
    i->callback(numbercb);

  }

  //Math function buttons!
  x = {20,140,260,380,380,380,380,380,260};
  y = {140,140,140,140,232,324,416,508,508};
  vector<char*> labels = {"√","^","+/-","DEL","÷","×","-","+","="};
  
  for (int i = 0; i < 9; i++) {
    OperatorButton *function = new OperatorButton(x[i],y[i],100,68,labels[i],labels[i]);
    operatorButtons.push_back(function);
  }

  for (auto i : operatorButtons) {
    i->color(c);
    i->labelcolor(FL_WHITE);
    i->labelsize(24);
  }

  for (auto i : operatorButtons) {
    i->callback(functioncb);
  }

  window->end();
  window->show(argc,argv);
  return Fl::run();
}
