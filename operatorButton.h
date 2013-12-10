#include <FL/FL_Button.H>

class OperatorButton : public Fl_Button {
 private:
  char symbol;
 public:
  OperatorButton(int,int,int,int,char*,char);
  char getOperator();
};
