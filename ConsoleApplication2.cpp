#include <iostream>
#include <cctype>  // For isdigit, isalpha, etc.
using namespace std;

// Token types
enum class TokenType {
    IDENTIFIER, // 0
    INT_LETRAL, // 1
    FLOAT_LETRAL, // 2
    PLUSE_OP, //3
    SUB_OP, //4
    DIV_OP, //5
    EXP_OP, //6
    MULTI_OP, //7
    STRING,     // 8
    RESERVED_WORD,    // 9
    END,        // 10
    LE_comparizon, // 11
    RE_comparizon, //12
    L_BRACET, //13
    R_BRACET, //14
    L_PAREN, //15
    R_PAREN, //16
    L_BRACES, //17
    R_BRACES, //18
    SEMICOLON,//19
    INVALID     // 20
};

class Token {
public:
    TokenType type;
    string value;
};

Token nextToken() {
    char c;
    while (cin.get(c) && isspace(c));

    if (cin.eof()) return { TokenType::END, "EOF" };

    switch (c) {
    case '+':
        return{ TokenType::PLUSE_OP,string(1,c) };
    case '-':
        return{ TokenType::SUB_OP,string(1,c) };
    case '*':
        return{ TokenType::MULTI_OP,string(1,c) };
    case '/':
        return{ TokenType::DIV_OP,string(1,c) };
    case ';':
        return{ TokenType::SEMICOLON,string(1,c) };
    case '"': {
        string str;
        while (cin.get(c) && c != '"') str += c;
        return { TokenType::STRING, str };
    }
    case '<':
        return { TokenType::LE_comparizon, string(1,c) };
    case '>':
        return { TokenType::RE_comparizon, string(1, c) };
    case '[':
        return{ TokenType::L_BRACET, string(1,c) };
    case ']':
        return { TokenType::R_BRACET, string(1,c) };
    case '{':
        return{ TokenType::L_BRACES, string(1,c) };
    case '}':
        return{ TokenType::R_BRACES, string(1,c) };
    case '(':
        return{ TokenType::L_PAREN,string(1,c) };
    case ')':
        return{ TokenType::R_PAREN,string(1,c) };
    case '^':
        return{ TokenType::EXP_OP,string(1,c) };
    default:
        if (isdigit(c)) {
            string num(1, c);
            bool hasDot = false;

            while (cin.get(c) && (isdigit(c) || c == '.')) {
                if (c == '.') {
                    if (hasDot) break; // More than one dot, stop parsing
                    hasDot = true;
                }
                num += c;
            }
            cin.unget();

            return { hasDot ? TokenType::FLOAT_LETRAL : TokenType::INT_LETRAL, num };
        }
        else if (isalpha(c)) {
            string id(1, c);
            while (cin.get(c) && isalnum(c)) id += c;
            cin.unget();
            if (id == "if" || id == "while" || id == "return" || id == "for")
                return { TokenType::RESERVED_WORD, id };
            return { TokenType::IDENTIFIER, id };
        }
        else {
            return { TokenType::INVALID, string(1, c) };
        }
    }
}

int main() {
    cout << "Enter code (CTRL+C to end):\n";

    while (true) {
        Token token = nextToken();
        cout << "Token(" << token.value << ", " << static_cast<int>(token.type) << ")\n";
        if (token.type == TokenType::END) break;
    }

    return 0;
}
