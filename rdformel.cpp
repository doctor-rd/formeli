#include <stdlib.h>
#include <string_view>
#include <iostream>
#include "rdformel.h"

#define Z result.m_char=*Test; position++; return result;
#define F(name, value)         \
if(result=getFunction(name)) { \
    result.m_char=value;       \
    return result;             \
}

int position;

const std::string_view digits("0123456789.E");

static bool is_digit(char c) {
    return digits.find(c) != std::string_view::npos;
}

double RDFormel::getZahl()
{
 char *Zahl=new char[50];
 int i=0;
 double Back;

 while(is_digit(Rechnung[position]) || Rechnung[position-1]=='E') {
  Zahl[i]=Rechnung[position];
  i++;
  position++;
 }
 Zahl[i]=0;

 Back=atof(Zahl);
 delete Zahl;
 return Back;
}

Token RDFormel::getFunction(std::string_view name) {
    Token result;
    auto len=name.length();
    if (expression.compare(position, len, name)!=0) {
        result.m_length=0;
        return result;
    }
    result.m_length=len;
    position+=len;
    result.m_type=TokenType::Function;
    return result;
}

Token RDFormel::getNextToken() {
 Token result;
 char *Test;
 Nochmal:
 Test=Rechnung+position;

 switch(*Test)
 {
  case 0   : Z
  case ' ' : position++; goto Nochmal;
  case '+' : Z
  case '/' : Z
  case '-' : Z
  case '*' : Z
  case '(' : Z
  case ')' : Z
  case '^' : Z
  case '!' : Z
 }

 if(*Test>='A' && *Test<='Z')
 {
  result.m_char=*Test;
  position++;
  if (!vars.contains(result.m_char)) {
   std::cout<<"unexpected variable "<<*Test<<"\n";
   result.m_char='?';
  }
  result.m_type = TokenType::Variable;
  return result;
 }

    F("e", E)
    F("ln", LN)
    F("log", LOG)
    F("pi", PI)
    F("sqrt", WURZEL)
    F("sinh", SINH)
    F("cosh", COSH)
    F("tanh", TANH)
    F("coth", COTH)
    F("sin", SIN)
    F("cos", COS)
    F("tan", TAN)
    F("cot", COT)
    F("arcsin", ASIN)
    F("arccos", ACOS)
    F("arctan", ATAN)
    F("arccot", ACOT)

 if((*Test>='x' && *Test<='y') || *Test=='t')
 {
  result.m_char=*Test+'A'-'a';
  position++;
  if (!vars.contains(result.m_char)) {
   std::cout<<"unexpected variable "<<*Test<<"\n";
   result.m_char='?';
  }
  result.m_type = TokenType::Variable;
  return result;
 }

 if(is_digit(Rechnung[position]))
 {
  result.m_number=getZahl();
  result.m_type = TokenType::Number;
  return result;
 }
 result.m_char='?';
 position++;
 return result;
}
