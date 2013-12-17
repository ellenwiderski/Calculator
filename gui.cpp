#include <cstdlib>
#include <cstdio>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <stack>
#include <string>
#include <math.h>
#include "operandButton.h"
#include "operatorButton.h"
#include <iostream>
using namespace std;

//Global Variables:
Fl_Box *number;
vector<OperandButton*> operandButtons;
vector<OperatorButton*> operatorButtons;
stack<float> operandStack;
vector<string> digits;
vector<Fl_Box*> screens;


void scoochdown() {
  screens[0]->copy_label("");
  stack<float> temp;
  int numloops = operandStack.size();

  for (auto i : screens) {
    i->copy_label("");
  }

  for (int i=1; i < numloops+1; i++) {
    if (i < 4) {
      screens[i]->copy_label(to_string(operandStack.top()).c_str());
      temp.push(operandStack.top());
     operandStack.pop();
    }
  }
  
  numloops = temp.size();
  
  for (int j = 0; j < numloops; j++) {
    operandStack.push(temp.top());
    temp.pop();
  }

}

//Callbacks:

void numbercb(Fl_Widget * w, void *) {
  OperandButton *numbutton = (OperandButton *)w;

  digits.push_back(to_string(numbutton->getOperand()));
  
  string num = "";
  for (auto i : digits) {
    num += i;
  }

  screens[0]->copy_label(num.c_str());
}

void entercb(Fl_Widget * w, void *) {
  if (digits.size() > 0) {
    string num = "";
    for (auto i : digits) {
      num += i;
    }
    digits.clear();
    operandStack.push(stof(num));
  }

  scoochdown();

}



void functioncb(Fl_Widget * w, void *) {
  OperatorButton *op = (OperatorButton *)w;

  char function = op->getOperator();

  if (operandStack.size() > 1) {

    float num1 = operandStack.top();
    operandStack.pop();
    float num2 = operandStack.top();
    operandStack.pop();
  
    float ans = 0.0;

    switch (function) {
    
    case '+' :
      {
    	ans = num1 + num2;
    	break;
      }
    case '-' :
      {
    	ans = num2 - num1;
    	break;
      }
    case '*' :
      {
    	ans = num1 * num2;
    	break;
      }
    case '/' :
      {
    	ans = num2 / num1;
    	break;
      }
    case 'p' :
      {
    	ans = pow(num2, num1);
      }
    }

    screens[1]->copy_label(to_string(ans).c_str());
    operandStack.push(ans);

    scoochdown();

    }
}

void dropcb(Fl_Widget * w, void *) {

  if (operandStack.size() > 0) {
    operandStack.pop();
  }
  if (operandStack.size() == 0) {
    screens[0]->copy_label("");
  }
  else {
    screens[0]->copy_label(to_string(operandStack.top()).c_str());
  }

  scoochdown();
}

void signcb(Fl_Widget * w, void *) {
  if (operandStack.size() > 0) {
    float num = operandStack.top();
    operandStack.pop();
    num = num * -1;
    operandStack.push(num);
    screens[0]->copy_label(to_string(operandStack.top()).c_str());
  }
}

void squarerootcb(Fl_Widget * w, void *) {
  if (operandStack.size() > 0) {

    float ans = 0.0;

    ans = sqrt(operandStack.top());
    operandStack.pop();
    screens[0]->copy_label(to_string(ans).c_str());
    operandStack.push(ans);
  }
  scoochdown();
}

void clearcb(Fl_Widget * w, void *) {
  int numloops = operandStack.size();
  for (int i = 0; i < numloops; i++) {
    operandStack.pop();
  }
  scoochdown();
}

//Main:
int main(int argc, char* argv[]) {
  Fl_Window *window = new Fl_Window(500,760);
  
  vector<int> y = {230,160,90,20};

  Fl_Color c = fl_rgb_color(240, 208, 255);

  for (int i = 0; i < 4; i++) {
    Fl_Box *screen = new Fl_Box(20,y[i],460,50,"");
    screen->box(FL_EMBOSSED_BOX);
    screen->labelsize(24);
    // Purple!
    screen->color(c);
    screens.push_back(screen);
  }

  y.clear();

  //Make the number buttons!
  vector<int> x = {20,20,140,260,20,140,260,20,140,260};
  y = {508,416,416,416,324,324,324,232,232,232};
  c = fl_rgb_color(73,7,90);

  for (int i = 0; i < 10; i++) {
      OperandButton *num = new OperandButton(x[i],y[i]+160,100,68,"",i);
      operandButtons.push_back(num);
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
  x = {140,380,380,380,380};
  y = {140,232,324,416,508};
  vector<char*> labels = {"^","÷","×","-","+"};
  vector<char> symbols = {'p','/','*','-','+'};
  
  for (int i = 0; i < 5; i++) {
    OperatorButton *function = new OperatorButton(x[i],y[i]+160,100,68,labels[i],symbols[i]);
    operatorButtons.push_back(function);
  }

  for (auto i : operatorButtons) {
    i->callback(functioncb);
  }

  Fl_Button *enter = new Fl_Button(260,668,100,68,"ENTER");
  enter->callback(entercb);
  enter->color(c);
  enter->labelcolor(FL_WHITE);
  enter->labelsize(24);

  Fl_Button *drop = new Fl_Button(260,300,100,68,"DROP");
  drop->callback(dropcb);
  drop->color(c);
  drop->labelcolor(FL_WHITE);
  drop->labelsize(24);

  Fl_Button *sqrt = new Fl_Button(20,300,100,68,"√");
  sqrt->callback(squarerootcb);
  sqrt->color(c);
  sqrt->labelcolor(FL_WHITE);
  sqrt->labelsize(24);

  Fl_Button *sign = new Fl_Button(140,668,100,68,"+/-");
  sign->callback(signcb);
  sign->color(c);
  sign->labelcolor(FL_WHITE);
  sign->labelsize(24);

  Fl_Button *clear = new Fl_Button(380,300,100,68,"CLR");
  clear->callback(clearcb);
  clear->color(c);
  clear->labelcolor(FL_WHITE);
  clear->labelsize(24);


  for (auto i : operatorButtons) {
    i->color(c);
    i->labelcolor(FL_WHITE);
    i->labelsize(24);
  }

  window->end();
  window->show(argc,argv);
  return Fl::run();
}
