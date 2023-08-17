#include <stdlib.h>
#include <string>
#include <string_view>
#include <iostream>
#include "token_var.h"

#define Z result.m_char=Test; position++; return result;
#define F(name, value)         \
if(result=getFunction(name)) { \
    result.m_char=value;       \
    return result;             \
}

const std::string_view digits("0123456789.E");

static bool is_digit(char c) {
    return digits.find(c) != std::string_view::npos;
}

Token TokenVar::getNumber() {
    Token result;
    std::string number;
    char ch;
    while (position<expression.length()) {
        if (!is_digit(ch=expression.at(position)))
            break;
        number.append(1, ch);
        position++;
    }
    result.m_length=number.length();
    result.m_type=TokenType::Number;
    result.m_number=atof(number.c_str());
    return result;
}

Token TokenVar::getFunction(std::string_view name) {
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

Token TokenVar::getNextToken() {
 Token result;
    char Test;
 Nochmal:
    if (position>=expression.length()) {
        result.m_char=0;
        return result;
    }
    Test=expression.at(position);

 switch(Test)
 {
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

 if(Test>='A' && Test<='Z') {
  result.m_char=Test;
  position++;
  if (!vars.contains(result.m_char)) {
   std::cout<<"unexpected variable "<<Test<<"\n";
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

 if((Test>='x' && Test<='y') || Test=='t') {
  result.m_char=Test+'A'-'a';
  position++;
  if (!vars.contains(result.m_char)) {
   std::cout<<"unexpected variable "<<Test<<"\n";
   result.m_char='?';
  }
  result.m_type = TokenType::Variable;
  return result;
 }

    if(is_digit(expression.at(position))) {
        result=getNumber();
        return result;
    }
 result.m_char='?';
 position++;
 return result;
}
