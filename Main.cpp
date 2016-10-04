#include "OptionChecker.h"
#include "Motor.h"

int main(int argc, char *argv[]) {
  OptionChecker a = OptionChecker(argc,argv);
  Motor m = Motor(a.getnbPeople(), a.getnbThread());
}
