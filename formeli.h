#include "rdformel.h"

class Formeli:public RDFormel
{
 public:
  //Konstruktor
  Formeli(char *frei);
  Formeli();
  //Destruktor
  ~Formeli();
  //Liefert das Ergebnis von Rechnung zurück
  double Ergebnis();
  //Setzt eine Variable die durch Buch gegeben ist auf den Wert, der in Wert gegeben ist.
  void SetVar(char Buch,double Wert);
  //Zeiger auf die Variablen A-Z
  double *Vars;
  //Wird auf true gesetzt, falls ein Rechenfehler auftritt
  bool Fehler;

 private:
  double StrichRech();
  double PotRech(double);
  double PunktRech(double);
  double SpezFunc(Token);
  double Wurzel();
  double ifunc();

  inline double fak(double in);
  inline double sqrtrd(double);
  inline double sinrd(double);
  inline double cosrd(double);
  inline double tanrd(double);
  inline double cotrd(double);
  inline double acotrd(double);
  inline double asinrd(double);
  inline double acosrd(double);
  inline double cothrd(double);
  inline double logrd(double);
  inline double log10rd(double);
  inline void divrd(double&,double);
  inline double powrd(double,double);
};
