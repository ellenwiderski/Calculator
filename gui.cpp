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
using namespace std;

//Global Variables:
vector<Fl_Button*> numberbuttons;
vector<Fl_Button*> functionbuttons;

//Callbacks:

//Main:
int main(int argc, char* argv[]) {
  Fl_Window *window = new Fl_Window(500,600);
  
  Fl_Box *screen = new Fl_Box(20,20,460,100,"");
  screen->box(FL_EMBOSSED_BOX);
  // Purple!
  Fl_Color c = fl_rgb_color(240, 208, 255);
  screen->color(c);


  //Make the number buttons!
  vector<int> x = {20,20,140,260,20,140,260,20,140,260};
  vector<int> y = {508,416,416,416,324,324,324,232,232,232};
  c = fl_rgb_color(73,7,90);

  for (int i = 0; i < 10; i++) {
    if (i == 0) {
      Fl_Button *num = new Fl_Button(x[i],y[i],220,68,"");
      numberbuttons.push_back(num);
    }
    else{
      Fl_Button *num = new Fl_Button(x[i],y[i],100,68,"");
      numberbuttons.push_back(num);
    }
  }

  //Give those beautiful number buttons some labels & color
  int pos = 0;
  for (auto i : numberbuttons) {
    i->copy_label(to_string(pos).c_str());
    i->color(c);
    i->labelcolor(FL_WHITE);
    i->labelsize(24);
    pos++;
  }
  
  x.clear();
  y.clear();

  //Let's set their callbacks!

  //Math function buttons!
  x = {20,140,260,380,380,380,380,380,260};
  y = {140,140,140,140,232,324,416,508,508};
  vector<char*> labels = {"√","^","+/-","DEL","÷","×","-","+","="};
  
  for (int i = 0; i < 9; i++) {
    Fl_Button *function = new Fl_Button(x[i],y[i],100,68,labels[i]);
    functionbuttons.push_back(function);
  }

  for (auto i : functionbuttons) {
    i->color(c);
    i->labelcolor(FL_WHITE);
    i->labelsize(24);
  }


  window->end();
  window->show(argc,argv);
  return Fl::run();
}
