#include <string.h>
#include <math.h>
#include <stdlib.h>
#pragma hdrstop
#include "rdformel.h"

#define Z *(char*) Daten=*Test; position++; return false;

char Zahlen[]="0123456789.E";
int position;
char SpezLaenge;
char Spezial;

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

bool RDFormel::getpart(void *Daten)
{
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
  Spezial=*Test;
  *(char*)Daten='S';
  position++;
  SpezLaenge=1;
  if(!aktiv[Spezial-'A'])
   *(char*)Daten='?';
  return false;
 }

 if(enthalten(Test,"e"))
 {
  Spezial=E;
  *(char*)Daten='S';
  position++;
  SpezLaenge=1;
  return false;
 }

 if(enthalten(Test,"ln"))
 {
  Spezial=LN;
  *(char*)Daten='S';
  position+=2;
  SpezLaenge=2;
  return false;
 }

 if(enthalten(Test,"log"))
 {
  Spezial=LOG;
  *(char*)Daten='S';
  position+=3;
  SpezLaenge=3;
  return false;
 }

 if(enthalten(Test,"pi"))
 {
  Spezial=PI;
  *(char*)Daten='S';
  position+=2;
  SpezLaenge=2;
  return false;
 }

 if(enthalten(Test,"sqrt"))
 {
  Spezial=WURZEL;
  *(char*)Daten='S';
  position+=4;
  SpezLaenge=4;
  return false;
 }
 if(enthalten(Test,"sinh"))
 {
  Spezial=SINH;
  *(char*)Daten='S';
  position+=4;
  SpezLaenge=4;
  return false;
 }
 if(enthalten(Test,"cosh"))
 {
  Spezial=COSH;
  *(char*)Daten='S';
  position+=4;
  SpezLaenge=4;
  return false;
 }
 if(enthalten(Test,"tanh"))
 {
  Spezial=TANH;
  *(char*)Daten='S';
  position+=4;
  SpezLaenge=4;
  return false;
 }
 if(enthalten(Test,"coth"))
 {
  Spezial=COTH;
  *(char*)Daten='S';
  position+=4;
  SpezLaenge=4;
  return false;
 }
 if(enthalten(Test,"sin"))
 {
  Spezial=SIN;
  *(char*)Daten='S';
  position+=3;
  SpezLaenge=3;
  return false;
 }
 if(enthalten(Test,"cos"))
 {
  Spezial=COS;
  *(char*)Daten='S';
  position+=3;
  SpezLaenge=3;
  return false;
 }
 if(enthalten(Test,"tan"))
 {
  Spezial=TAN;
  *(char*)Daten='S';
  position+=3;
  SpezLaenge=3;
  return false;
 }

 if(enthalten(Test,"cot"))
 {
  Spezial=COT;
  *(char*)Daten='S';
  position+=3;
  SpezLaenge=3;
  return false;
 }

 if(enthalten(Test,"arcsin"))
 {
  Spezial=ASIN;
  *(char*)Daten='S';
  position+=6;
  SpezLaenge=6;
  return false;
 }
 if(enthalten(Test,"arccos"))
 {
  Spezial=ACOS;
  *(char*)Daten='S';
  position+=6;
  SpezLaenge=6;
  return false;
 }
 if(enthalten(Test,"arctan"))
 {
  Spezial=ATAN;
  *(char*)Daten='S';
  position+=6;
  SpezLaenge=6;
  return false;
 }
 if(enthalten(Test,"arccot"))
 {
  Spezial=ACOT;
  *(char*)Daten='S';
  position+=6;
  SpezLaenge=6;
  return false;
 }

 if((*Test>='x' && *Test<='y') || *Test=='t')
 {
  *(char*)Daten='S';
  Spezial=*Test+'A'-'a';
  position++;
  SpezLaenge=1;
  if(!aktiv[Spezial-'A'])
   *(char*)Daten='?';
  return false;
 }

 if(Ziffer(Rechnung[position]))
 {
  *(double*)Daten=getZahl();
  return true;
 }
 *(char*)Daten='?';
 position++;
 return false;
}
