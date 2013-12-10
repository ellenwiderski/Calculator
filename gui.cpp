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
using namespace std;

//Global Variables:
Fl_Box *number;
vector<OperandButton*> operandButtons;
vector<OperatorButton*> operatorButtons;
stack<string> operandStack;
vector<string> digits;

//Callbacks:

void numbercb(Fl_Widget * w, void *) {
  OperandButton *numbutton = (OperandButton *)w;

  digits.push_back(to_string(numbutton->getOperand()));
  
  string num = "";
  for (auto i : digits) {
    num += i;
  }

  number->copy_label(num.c_str());
}

void functioncb(Fl_Widget * w, void *) {
  OperatorButton *op = (OperatorButton *)w;

  char function = op->getOperator();

  if (operandStack.size() > 1) {

    float num1 = stof(operandStack.top());
    operandStack.pop();
    float num2 = stof(operandStack.top());
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

    number->copy_label(to_string(ans).c_str());
    operandStack.push(to_string(ans));
    }
}

void entercb(Fl_Widget * w, void *) {
  if (digits.size() > 0) {
    string num = "";
    for (auto i : digits) {
      num += i;
    }
    digits.clear();
    operandStack.push(num);
  }
}

void dropcb(Fl_Widget * w, void *) {
  if (operandStack.size() > 0) {
    operandStack.pop();
  }
}

void signcb(Fl_Widget * w, void *) {
  if (operandStack.size() > 0) {
    string num = operandStack.top();
    operandStack.pop();
    num = "-" + num;
    operandStack.push(num);
    number->copy_label(operandStack.top().c_str());
  }
}

void squarerootcb(Fl_Widget * w, void *) {
  if (operandStack.size() > 0) {

    float ans = 0.0;

    ans = sqrt(stof(operandStack.top()));
    operandStack.pop();
    number->copy_label(to_string(ans).c_str());
    operandStack.push(to_string(ans));
  }
}

//Main:
int main(int argc, char* argv[]) {
  Fl_Window *window = new Fl_Window(500,600);
  
  Fl_Box *screen = new Fl_Box(20,20,460,100,"");
  screen->box(FL_EMBOSSED_BOX);
  number = new Fl_Box(20,20,460,100,"");
  number->align(FL_ALIGN_CENTER);
  number->labelsize(48);
  // Purple!
  Fl_Color c = fl_rgb_color(240, 208, 255);
  screen->color(c);


  //Make the number buttons!
  vector<int> x = {20,20,140,260,20,140,260,20,140,260};
  vector<int> y = {508,416,416,416,324,324,324,232,232,232};
  c = fl_rgb_color(73,7,90);

  for (int i = 0; i < 10; i++) {
    if (i != 0) {
      OperandButton *num = new OperandButton(x[i],y[i],100,68,"",i);
      operandButtons.push_back(num);
    }
    else {
      OperandButton *num = new OperandButton(x[i],y[i],220,68,"",i);
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
  x = {140,380,380,380,380};
  y = {140,232,324,416,508};
  vector<char*> labels = {"^","÷","×","-","+"};
  vector<char> symbols = {'p','/','*','-','+'};
  
  for (int i = 0; i < 5; i++) {
    OperatorButton *function = new OperatorButton(x[i],y[i],100,68,labels[i],symbols[i]);
    operatorButtons.push_back(function);
  }

  for (auto i : operatorButtons) {
    i->callback(functioncb);
  }

  Fl_Button *enter = new Fl_Button(260,508,100,68,"ENTER");
  enter->callback(entercb);
  enter->color(c);
  enter->labelcolor(FL_WHITE);
  enter->labelsize(24);

  Fl_Button *drop = new Fl_Button(380,140,100,68,"DROP");
  drop->callback(dropcb);
  drop->color(c);
  drop->labelcolor(FL_WHITE);
  drop->labelsize(24);

  Fl_Button *sqrt = new Fl_Button(20,140,100,68,"√");
  sqrt->callback(squarerootcb);
  sqrt->color(c);
  sqrt->labelcolor(FL_WHITE);
  sqrt->labelsize(24);

  Fl_Button *sign = new Fl_Button(260,140,100,68,"+/-");
  sign->callback(signcb);
  sign->color(c);
  sign->labelcolor(FL_WHITE);
  sign->labelsize(24);


  for (auto i : operatorButtons) {
    i->color(c);
    i->labelcolor(FL_WHITE);
    i->labelsize(24);
  }

  window->end();
  window->show(argc,argv);
  return Fl::run();
}
