#include<map>
#include<string_view>

enum Spezials{SINH,COSH,TANH,COTH,E,PI,LN,LOG,SIN,COS,TAN,COT,ASIN,ACOS,ATAN,ACOT,WURZEL};

enum class TokenType {
    None,
    Number,
    Variable,
    Function,
};

struct Token {
    TokenType m_type {TokenType::None};
    int m_length {1};
    double m_number;
    char m_char;

    bool is_number() const {
        return m_type == TokenType::Number;
    }

    bool is_special() const {
        return m_type == TokenType::Variable || m_type == TokenType::Function;
    }

    operator bool() const {
        return m_length>0;
    }
};

class RDFormel
{
public:
    std::string_view expression;
    std::map<char, double> vars;

protected:
    [[nodiscard]] Token getNextToken();
    int position;

private:
    [[nodiscard]] Token getFunction(std::string_view);
    [[nodiscard]] Token getNumber();
};
