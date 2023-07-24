#include <iostream>
#include "formeli.h"

int main(int argc, char *argv[]) {
  Formeli formel;
  formel.expression=argv[1];
  std::cout<<formel.Ergebnis()<<std::endl;
  return 0;
}
