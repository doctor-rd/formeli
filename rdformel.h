#define ALL "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NONE ""
enum Spezials{SINH,COSH,TANH,COTH,E,PI,LN,LOG,SIN,COS,TAN,COT,ASIN,ACOS,ATAN,ACOT,WURZEL};

extern int position;
extern char SpezLaenge;
extern char Spezial;

bool enthalten(char *Text, char *enth);

class RDFormel
{
 public:
  //Konstruktor
  RDFormel(char*);
  //Destruktor
  ~RDFormel();
  //Zeiger auf den String mit der Rechnung
  char *Rechnung;

 protected:
  bool getpart(void *Daten);

 private:
  bool *aktiv;
  double getZahl();
};
