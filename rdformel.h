#define ALL "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NONE ""
enum Spezials{SINH,COSH,TANH,COTH,E,PI,LN,LOG,SIN,COS,TAN,COT,ASIN,ACOS,ATAN,ACOT,WURZEL};

extern int position;
extern char SpezLaenge;

bool enthalten(char *Text, char *enth);

enum class TokenType {
    None,
    Number,
    Variable,
    Function,
};

struct Token {
    TokenType m_type {TokenType::None};
    double m_number;
    char m_char;

    bool is_number() const {
        return m_type == TokenType::Number;
    }

    bool is_special() const {
        return m_type == TokenType::Variable || m_type == TokenType::Function;
    }
};

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
    [[nodiscard]] Token getNextToken();

 private:
  bool *aktiv;
  double getZahl();
};
