#include <math.h>
#include <string.h>
#pragma hdrstop
#include "formeli.h"

void Formeli::SetVar(char Buch,double Wert)
{
 Vars[Buch-'A']=Wert;
}

double Formeli::Ergebnis()
{
 position=0;
 Fehler=false;
 return StrichRech();
}

Formeli::Formeli():RDFormel(NONE)
{
 Vars=new double[26];
}

Formeli::Formeli(char *frei):RDFormel(frei)
{
 Vars=new double[26];
}

Formeli::~Formeli()
{
 delete Vars;
}

double Formeli::Wurzel()
{
 void *Daten=new double;
 double Erg;

 Nochmal:
 if(getpart(Daten))
  Erg=sqrt(PotRech(*(double*)Daten));
 else
 {
  if(*(char*)Daten=='S')
   Erg=sqrtrd(PotRech(SpezFunc()));
  if(*(char*)Daten=='(')
   Erg=sqrtrd(PotRech(StrichRech()));
  if(*(char*)Daten=='+')
   goto Nochmal;
  if(*(char*)Daten=='-')
   if(getpart(Daten))
    Erg=sqrtrd(-PotRech(*(double*)Daten));
   else
   {
    if(*(char*)Daten=='(')
     Erg=sqrtrd(-PotRech(StrichRech()));
    if(*(char*)Daten=='S')
     Erg=sqrtrd(-PotRech(SpezFunc()));
   }
 }
 delete Daten;
 return Erg;
}

double Formeli::ifunc()
{
 void *Daten=new double;
 double Erg;

 Nochmal:
 if(getpart(Daten))
  Erg=PunktRech(*(double*)Daten);
 else
 {
  if(*(char*)Daten=='S')
   Erg=PunktRech(SpezFunc());
  if(*(char*)Daten=='(')
  {
   position--;
   Erg=PunktRech(1);
  }
  if(*(char*)Daten=='+')
   goto Nochmal;
  if(*(char*)Daten=='-')
   if(getpart(Daten))
    Erg=-PunktRech(*(double*)Daten);
   else
   {
    if(*(char*)Daten=='S')
     Erg=-PunktRech(SpezFunc());
    if(*(char*)Daten=='(')
    {
     position--;
     Erg=-PunktRech(1);
    }
   }
 }
 delete Daten;
 return Erg;
}

double Formeli::SpezFunc()
{
 switch(Spezial)
 {
  case WURZEL : return Wurzel();
  case PI : return PotRech(pi);
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
 if(Spezial>='A' && Spezial<='Z')
  return PotRech(Vars[Spezial-'A']);
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
 void *Daten=new double;

 getpart(Daten);
 switch(*(char*)Daten)
 {
  case 0   : position--; break;
  case ')' : position--; break;
  case '(' : position--; break;
  case '+' : position--; break;
  case '-' : position--; break;
  case '*' : position--; break;
  case '/' : position--; break;
  case 'S' : position-=SpezLaenge; break;
  case '!' : Erg=PotRech(fak(Erg)); break;
  case '^' : Nochmal:
	     if(getpart(Daten))
              Erg=powrd(Erg,PotRech(*(double*)Daten));
             else
             {
              if(*(char*)Daten=='(')
               Erg=powrd(Erg,PotRech(StrichRech()));
              if(*(char*)Daten=='S')
               Erg=powrd(Erg,SpezFunc());
              if(*(char*)Daten=='+')
               goto Nochmal;
              if(*(char*)Daten=='-')
               if(getpart(Daten))
                Erg=powrd(Erg,-PotRech(*(double*)Daten));
               else
               {
                if(*(char*)Daten=='(')
                 Erg=powrd(Erg,-PotRech(StrichRech()));
                if(*(char*)Daten=='S')
                 Erg=powrd(Erg,-SpezFunc());
               }
             }
 }

 delete Daten;
 return Erg;
}

double Formeli::PunktRech(double erste)
{
 double Erg=PotRech(erste);
 void *Daten=new double;
 bool ok=true;

 while(ok)
 {
  getpart(Daten);
  switch(*(char*)Daten)
  {
   case ')' : position--; ok=false; break;
   case 0   : position--; ok=false; break;
   case '-' : position--; ok=false; break;
   case '+' : position--; ok=false; break;
   case '*' : Nochmalm:
              if(getpart(Daten))
               Erg*=PotRech(*(double*)Daten);
              else
              {
               if(*(char*) Daten=='S')
                Erg*=SpezFunc();
               if(*(char*) Daten=='(')
                Erg*=PotRech(StrichRech());
               if(*(char*) Daten=='+')
                goto Nochmalm;
               if(*(char*) Daten=='-')
                if(getpart(Daten))
                 Erg*=-PotRech(*(double*)Daten);
                else
                {
                 if(*(char*) Daten=='(')
                  Erg*=-PotRech(StrichRech());
                 if(*(char*) Daten=='S')
                  Erg*=-SpezFunc();
                }
              }
              break;
   case '/' : Nochmald:
              if(getpart(Daten))
               divrd(Erg,PotRech(*(double*)Daten));
              else
              {
               if(*(char*) Daten=='S')
                divrd(Erg,SpezFunc());
               if(*(char*) Daten=='(')
                divrd(Erg,PotRech(StrichRech()));
               if(*(char*) Daten=='+')
                goto Nochmald;
               if(*(char*) Daten=='-')
                if(getpart(Daten))
                 divrd(Erg,-PotRech(*(double*)Daten));
                else
                {
                 if(*(char*) Daten=='S')
                  divrd(Erg,-SpezFunc());
                 if(*(char*) Daten=='(')
                  divrd(Erg,-PotRech(StrichRech()));
                }
              }
              break;
   case '(' : Erg*=PotRech(StrichRech()); break;
   case 'S' : Erg*=SpezFunc(); break;
  }
 }
 delete Daten;
 return Erg;
}

double Formeli::StrichRech()
{
 double Erg=0;
 bool ok=true;
 void *Daten=new double;

 Nochmal:
 if(getpart(Daten))
  Erg+=PunktRech(*(double*) Daten);
 else
 {
  if(*(char*) Daten=='(')
  {
   position--;
   Erg=PunktRech(1);
  }
  if(*(char*) Daten=='S')
   Erg=PunktRech(SpezFunc());
  if(*(char*) Daten=='+')
   goto Nochmal;
  if(*(char*) Daten=='-')
  {
   if(getpart(Daten))
    Erg-=PunktRech(*(double*) Daten);
   else
   {
    if(*(char*) Daten=='S')
     Erg=-PunktRech(SpezFunc());
    if(*(char*) Daten=='(')
    {
     position--;
     Erg=-PunktRech(1);
    }
   }
  }
 }

 while(ok)
 {
  getpart(Daten);
  switch(*(char*)Daten)
  {
   case ')' : ok=false; break;
   case 0   : position--; ok=false; break;
   case '+' : if(getpart(Daten))
               Erg+=PunktRech(*(double*)Daten);
              else
              {
               if(*(char*)Daten=='S')
                Erg+=PunktRech(SpezFunc());
               if(*(char*)Daten=='(')
               {
                position--;
                Erg+=PunktRech(1);
               }
              }
              break;
   case '-' : if(getpart(Daten))
               Erg-=PunktRech(*(double*)Daten);
              else
              {
               if(*(char*)Daten=='S')
                Erg-=PunktRech(SpezFunc());
               if(*(char*)Daten=='(')
               {
                position--;
                Erg-=PunktRech(1);
               }
              }
              break;
  }
 }

 delete Daten;
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
 //if(in==pi) return 0;

 double tmp=in/pi;

 if(tmp==(int)tmp)
  return 0;

 return sin(in);
}

inline double Formeli::cosrd(double in)
{
 return sinrd(in+pi/2);
}

inline double Formeli::tanrd(double in)
{
 double tmp=(in+pi/2)/pi;

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
