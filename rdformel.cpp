#include <string.h>
#include <math.h>
#include <stdlib.h>
#pragma hdrstop
#include "rdformel.h"

#define Z result.m_char=*Test; position++; return result;

char Zahlen[]="0123456789.E";
int position;
char SpezLaenge;

bool enthalten(char *Text, char *enth)
{
 bool gleich=true;
 for(char i=0;i<strlen(enth);i++)
  if(Text[i]!=enth[i])
   gleich=false;

 return gleich;
}

bool Ziffer(char Zeichen)
{
 for(char i=0;i<strlen(Zahlen);i++)
  if(Zahlen[i]==Zeichen)
   return true;

 return false;
}

RDFormel::RDFormel(char *frei)
{
 aktiv=new bool[26];

 for(int i=0;i<26;i++)
  aktiv[i]=false;

 for(int i=0;i<strlen(frei);i++)
  if(frei[i]>='A' && frei[i]<='Z')
   aktiv[frei[i]-'A']=true;
}

RDFormel::~RDFormel()
{
 delete aktiv;
}

double RDFormel::getZahl()
{
 char *Zahl=new char[50];
 int i=0;
 double Back;

 while(Ziffer(Rechnung[position]) || Rechnung[position-1]=='E')
 {
  Zahl[i]=Rechnung[position];
  i++;
  position++;
 }
 Zahl[i]=0;

 Back=atof(Zahl);
 delete Zahl;
 return Back;
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
  SpezLaenge=1;
  if(!aktiv[*Test-'A'])
   result.m_char='?';
  result.m_type = TokenType::Variable;
  return result;
 }

 if(enthalten(Test,"e"))
 {
  result.m_char=E;
  position++;
  SpezLaenge=1;
  result.m_type = TokenType::Function;
  return result;
 }

 if(enthalten(Test,"ln"))
 {
  result.m_char=LN;
  position+=2;
  SpezLaenge=2;
  result.m_type = TokenType::Function;
  return result;
 }

 if(enthalten(Test,"log"))
 {
  result.m_char=LOG;
  position+=3;
  SpezLaenge=3;
  result.m_type = TokenType::Function;
  return result;
 }

 if(enthalten(Test,"pi"))
 {
  result.m_char=PI;
  position+=2;
  SpezLaenge=2;
  result.m_type = TokenType::Function;
  return result;
 }

 if(enthalten(Test,"sqrt"))
 {
  result.m_char=WURZEL;
  position+=4;
  SpezLaenge=4;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"sinh"))
 {
  result.m_char=SINH;
  position+=4;
  SpezLaenge=4;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"cosh"))
 {
  result.m_char=COSH;
  position+=4;
  SpezLaenge=4;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"tanh"))
 {
  result.m_char=TANH;
  position+=4;
  SpezLaenge=4;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"coth"))
 {
  result.m_char=COTH;
  position+=4;
  SpezLaenge=4;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"sin"))
 {
  result.m_char=SIN;
  position+=3;
  SpezLaenge=3;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"cos"))
 {
  result.m_char=COS;
  position+=3;
  SpezLaenge=3;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"tan"))
 {
  result.m_char=TAN;
  position+=3;
  SpezLaenge=3;
  result.m_type = TokenType::Function;
  return result;
 }

 if(enthalten(Test,"cot"))
 {
  result.m_char=COT;
  position+=3;
  SpezLaenge=3;
  result.m_type = TokenType::Function;
  return result;
 }

 if(enthalten(Test,"arcsin"))
 {
  result.m_char=ASIN;
  position+=6;
  SpezLaenge=6;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"arccos"))
 {
  result.m_char=ACOS;
  position+=6;
  SpezLaenge=6;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"arctan"))
 {
  result.m_char=ATAN;
  position+=6;
  SpezLaenge=6;
  result.m_type = TokenType::Function;
  return result;
 }
 if(enthalten(Test,"arccot"))
 {
  result.m_char=ACOT;
  position+=6;
  SpezLaenge=6;
  result.m_type = TokenType::Function;
  return result;
 }

 if((*Test>='x' && *Test<='y') || *Test=='t')
 {
  result.m_char=*Test+'A'-'a';
  position++;
  SpezLaenge=1;
  if(!aktiv[*Test-'a'])
   result.m_char='?';
  result.m_type = TokenType::Variable;
  return result;
 }

 if(Ziffer(Rechnung[position]))
 {
  result.m_number=getZahl();
  result.m_type = TokenType::Number;
  return result;
 }
 result.m_char='?';
 position++;
 return result;
}
