#include <FL/FL_Button.H>

class OperandButton : public Fl_Button {
 private:
  int operand;
 public:
  OperandButton(int,int,int,int,char*,int);
  int getOperand();
};
