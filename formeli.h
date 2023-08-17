#include "token_var.h"

class Formeli : public TokenVar {
 public:
  //Liefert das Ergebnis von Rechnung zurück
  double Ergebnis();
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
