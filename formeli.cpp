#include <math.h>
#include <string.h>
#pragma hdrstop
#include "formeli.h"

double Formeli::Ergebnis()
{
 position=0;
 Fehler=false;
 return StrichRech();
}

double Formeli::Wurzel()
{
 Token token;
 double Erg;

 Nochmal:
 if((token=getNextToken()).is_number())
  Erg=sqrt(PotRech(token.m_number));
 else
 {
  if(token.is_special())
   Erg=sqrtrd(PotRech(SpezFunc(token)));
  if(token.m_char=='(')
   Erg=sqrtrd(PotRech(StrichRech()));
  if(token.m_char=='+')
   goto Nochmal;
  if(token.m_char=='-')
   if((token=getNextToken()).is_number())
    Erg=sqrtrd(-PotRech(token.m_number));
   else
   {
    if(token.m_char=='(')
     Erg=sqrtrd(-PotRech(StrichRech()));
    if(token.is_special())
     Erg=sqrtrd(-PotRech(SpezFunc(token)));
   }
 }
 return Erg;
}

double Formeli::ifunc()
{
 Token token;
 double Erg;

 Nochmal:
 if((token=getNextToken()).is_number())
  Erg=PunktRech(token.m_number);
 else
 {
  if(token.is_special())
   Erg=PunktRech(SpezFunc(token));
  if(token.m_char=='(')
  {
   position--;
   Erg=PunktRech(1);
  }
  if(token.m_char=='+')
   goto Nochmal;
  if(token.m_char=='-')
   if((token=getNextToken()).is_number())
    Erg=-PunktRech(token.m_number);
   else
   {
    if(token.is_special())
     Erg=-PunktRech(SpezFunc(token));
    if(token.m_char=='(')
    {
     position--;
     Erg=-PunktRech(1);
    }
   }
 }
 return Erg;
}

double Formeli::SpezFunc(Token token) {
 switch(token.m_char)
 {
  case WURZEL : return Wurzel();
  case PI : return PotRech(M_PI);
  case SIN : return sinrd(ifunc());
  case COS : return cosrd(ifunc());
  case TAN : return tanrd(ifunc());
  case COT : return cotrd(ifunc());
  case ASIN : return asinrd(ifunc());
  case ACOS : return acosrd(ifunc());
  case ATAN : return atan(ifunc());
  case ACOT : return acotrd(ifunc());
  case E : return PotRech(exp(1));
  case LN : return logrd(ifunc());
  case LOG : return log10rd(ifunc());
  case SINH : return sinh(ifunc());
  case COSH : return cosh(ifunc());
  case TANH : return tanh(ifunc());
  case COTH : return cothrd(ifunc());
 }
 if(token.m_char>='A' && token.m_char<='Z')
  return PotRech(vars[token.m_char]);
}

inline double Formeli::fak(double in)
{
 double Erg=1;
 if(in<0 || in>170)
 {
  Fehler=true;
  return 0;
 }

 for(unsigned int i=in;i>=1;i--)
  Erg*=i;

 return Erg;
}

double Formeli::PotRech(double erste)
{
 double Erg=erste;
 Token token;

 token=getNextToken();
 if (token.is_special()) {
  position-=SpezLaenge;
  return Erg;
 }
 switch(token.m_char)
 {
  case 0   : position--; break;
  case ')' : position--; break;
  case '(' : position--; break;
  case '+' : position--; break;
  case '-' : position--; break;
  case '*' : position--; break;
  case '/' : position--; break;
  case '!' : Erg=PotRech(fak(Erg)); break;
  case '^' : Nochmal:
	     if((token=getNextToken()).is_number())
              Erg=powrd(Erg,PotRech(token.m_number));
             else
             {
              if(token.m_char=='(')
               Erg=powrd(Erg,PotRech(StrichRech()));
              if(token.is_special())
               Erg=powrd(Erg,SpezFunc(token));
              if(token.m_char=='+')
               goto Nochmal;
              if(token.m_char=='-')
               if((token=getNextToken()).is_number())
                Erg=powrd(Erg,-PotRech(token.m_number));
               else
               {
                if(token.m_char=='(')
                 Erg=powrd(Erg,-PotRech(StrichRech()));
                if(token.is_special())
                 Erg=powrd(Erg,-SpezFunc(token));
               }
             }
 }

 return Erg;
}

double Formeli::PunktRech(double erste)
{
 double Erg=PotRech(erste);
 Token token;
 bool ok=true;

 while(ok)
 {
  token=getNextToken();
  if (token.is_special()) {
   Erg*=SpezFunc(token);
   continue;
  }
  switch(token.m_char)
  {
   case ')' : position--; ok=false; break;
   case 0   : position--; ok=false; break;
   case '-' : position--; ok=false; break;
   case '+' : position--; ok=false; break;
   case '*' : Nochmalm:
              if((token=getNextToken()).is_number())
               Erg*=PotRech(token.m_number);
              else
              {
               if(token.is_special())
                Erg*=SpezFunc(token);
               if(token.m_char=='(')
                Erg*=PotRech(StrichRech());
               if(token.m_char=='+')
                goto Nochmalm;
               if(token.m_char=='-')
                if((token=getNextToken()).is_number())
                 Erg*=-PotRech(token.m_number);
                else
                {
                 if(token.m_char=='(')
                  Erg*=-PotRech(StrichRech());
                 if(token.is_special())
                  Erg*=-SpezFunc(token);
                }
              }
              break;
   case '/' : Nochmald:
              if((token=getNextToken()).is_number())
               divrd(Erg, PotRech(token.m_number));
              else
              {
               if(token.is_special())
                divrd(Erg,SpezFunc(token));
               if(token.m_char=='(')
                divrd(Erg,PotRech(StrichRech()));
               if(token.m_char=='+')
                goto Nochmald;
               if(token.m_char=='-')
                if((token=getNextToken()).is_number())
                 divrd(Erg,-PotRech(token.m_number));
                else
                {
                 if(token.is_special())
                  divrd(Erg,-SpezFunc(token));
                 if(token.m_char=='(')
                  divrd(Erg,-PotRech(StrichRech()));
                }
              }
              break;
   case '(' : Erg*=PotRech(StrichRech()); break;
  }
 }
 return Erg;
}

double Formeli::StrichRech()
{
 double Erg=0;
 bool ok=true;
 Token token;

 Nochmal:
 if((token=getNextToken()).is_number())
  Erg+=PunktRech(token.m_number);
 else
 {
  if(token.m_char=='(')
  {
   position--;
   Erg=PunktRech(1);
  }
  if(token.is_special())
   Erg=PunktRech(SpezFunc(token));
  if(token.m_char=='+')
   goto Nochmal;
  if(token.m_char=='-')
  {
   if((token=getNextToken()).is_number())
    Erg-=PunktRech(token.m_number);
   else
   {
    if(token.is_special())
     Erg=-PunktRech(SpezFunc(token));
    if(token.m_char=='(')
    {
     position--;
     Erg=-PunktRech(1);
    }
   }
  }
 }

 while(ok)
 {
  token=getNextToken();
  switch(token.m_char)
  {
   case ')' : ok=false; break;
   case 0   : position--; ok=false; break;
   case '+' : if((token=getNextToken()).is_number())
               Erg+=PunktRech(token.m_number);
              else
              {
               if(token.is_special())
                Erg+=PunktRech(SpezFunc(token));
               if(token.m_char=='(')
               {
                position--;
                Erg+=PunktRech(1);
               }
              }
              break;
   case '-' : if((token=getNextToken()).is_number())
               Erg-=PunktRech(token.m_number);
              else
              {
               if(token.is_special())
                Erg-=PunktRech(SpezFunc(token));
               if(token.m_char=='(')
               {
                position--;
                Erg-=PunktRech(1);
               }
              }
              break;
  }
 }

 return Erg;
}

inline double Formeli::sqrtrd(double in)
{
 if(in<0)
  Fehler=true;
 else
  return sqrt(in);
 return 0;
}

inline double Formeli::sinrd(double in)
{
 double tmp=in/M_PI;

 if(tmp==(int)tmp)
  return 0;

 return sin(in);
}

inline double Formeli::cosrd(double in)
{
 return sinrd(in+M_PI/2);
}

inline double Formeli::tanrd(double in)
{
 double tmp=(in+M_PI/2)/M_PI;

 if(tmp==(int)tmp)
 {
  Fehler=true;
  return 0;
 }
 return tan(in);
}
inline double Formeli::cotrd(double in)
{
 double tmp=tanrd(in);
 if(tmp==0)
 {
  Fehler=true;
  return 0;
 }
 return 1/tmp;
}

inline double Formeli::asinrd(double in)
{
 if(in>1 || in<-1)
  Fehler=true;
 else
  return asin(in);
 return 0;
}

inline double Formeli::acosrd(double in)
{
 if(in>1 || in<-1)
  Fehler=true;
 else
  return acos(in);
 return 0;
}

inline double Formeli::logrd(double in)
{
 if(in<=0)
  Fehler=true;
 else
  return log(in);
 return 0;
}

inline double Formeli::log10rd(double in)
{
 if(in<=0)
  Fehler=true;
 else
  return log10(in);
 return 0;
}

inline void Formeli::divrd(double &a,double b)
{
 if(b==0)
  Fehler=true;
 else
  a/=b;
}

inline double Formeli::powrd(double b,double e)
{
 if(e<=0 && b==0)
 {
  Fehler=true;
  return 0;
 }
 if(b>=0 || e==(int)e)
// {
//  if((b>0 && log10(b)*e>308) || (b<0 && log10(-b)*e>308))
//  {
//   Fehler=true;
//   return 0;
//  }
  return pow(b,e);
// }
 else
 {
  const double rez=1/e;
  if((int)rez==rez && (int)rez&1==1)
   return -pow(-b,e);
 }
 Fehler=true;
 return 0;
}

inline double Formeli::cothrd(double in)
{
 double tmp=tanh(in);
 if(tmp==0)
 {
  Fehler=true;
  return 0;
 }
 return 1/tmp;
}

inline double Formeli::acotrd(double in)
{
 if(in==0)
 {
  Fehler=true;
  return 0;
 }
 return atan(1/in);
}
