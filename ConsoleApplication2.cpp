#include <iostream>
#include <cctype>  // For isdigit, isalpha, etc.
using namespace std;

// Token types
enum class TokenType {
    IDENTIFIER, // 0
    INT_LETRAL, // 1
    FLOAT_LETRAL, // 2
    PLUSE_OP, // 3
    SUB_OP, // 4
    DIV_OP, // 5
    EXP_OP, // 6
    MULTI_OP, // 7
    STRING, // 8
    RESERVED_WORD, // 9
    END, // 10
    L_comparizon, // 11
    R_comparizon, // 12
    L_BRACET, // 13
    R_BRACET, // 14
    L_PAREN, // 15
    R_PAREN, // 16
    L_BRACES, // 17
    R_BRACES, // 18
    SEMICOLON, // 19
    assign_op, // 20
    LE_comparizon, // 21
    RE_comparizon, // 22
    IF, // 23
    FOR, // 24
    WHILE, // 25
    INVALID // 26
};

class Token {
public:
    TokenType type;
    string value;
};

string tokenTypeToString(TokenType type) {
    switch (type) {
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::INT_LETRAL: return "INT_LITERAL";
    case TokenType::FLOAT_LETRAL: return "FLOAT_LITERAL";
    case TokenType::PLUSE_OP: return "PLUS_OP";
    case TokenType::SUB_OP: return "SUB_OP";
    case TokenType::MULTI_OP: return "MULTI_OP";
    case TokenType::DIV_OP: return "DIV_OP";
    case TokenType::EXP_OP: return "EXP_OP";
    case TokenType::STRING: return "STRING";
    case TokenType::RESERVED_WORD: return "RESERVED_WORD";
    case TokenType::END: return "END";
    case TokenType::L_comparizon: return "L_COMPARISON";
    case TokenType::R_comparizon: return "R_COMPARISON";
    case TokenType::LE_comparizon: return "LE_COMPARISON";
    case TokenType::RE_comparizon: return "RE_COMPARISON";
    case TokenType::L_BRACET: return "L_BRACKET";
    case TokenType::R_BRACET: return "R_BRACKET";
    case TokenType::L_PAREN: return "L_PAREN";
    case TokenType::R_PAREN: return "R_PAREN";
    case TokenType::L_BRACES: return "L_BRACES";
    case TokenType::R_BRACES: return "R_BRACES";
    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::assign_op: return "ASSIGN_OP";
    case TokenType::IF: return "IF";
    case TokenType::FOR: return "FOR";
    case TokenType::WHILE: return "WHILE";
    case TokenType::INVALID: return "INVALID";
    default: return "UNKNOWN";
    }
}

Token nextToken() {
    char c;
    while (cin.get(c) && isspace(c));  // Skip white spaces

    if (cin.eof()) return { TokenType::END, "EOF" };

    switch (c) {
    case '+':
        return { TokenType::PLUSE_OP, string(1, c) };
    case '-':
        return { TokenType::SUB_OP, string(1, c) };
    case '*':
        return { TokenType::MULTI_OP, string(1, c) };
    case '/':
        return { TokenType::DIV_OP, string(1, c) };
    case ';':
        return { TokenType::SEMICOLON, string(1, c) };
    case '"': {
        string str;
        while (cin.get(c) && c != '"') str += c;
        return { TokenType::STRING, str };
    }
    case '<': {
        if (cin.peek() == '=') {
            cin.get();
            return { TokenType::LE_comparizon, "<=" };
        }
        return { TokenType::L_comparizon, "<" };
    }
    case '>': {
        if (cin.peek() == '=') {
            cin.get();
            return { TokenType::RE_comparizon, ">=" };
        }
        return { TokenType::R_comparizon, ">" };
    }
    case '[':
        return { TokenType::L_BRACET, string(1, c) };
    case ']':
        return { TokenType::R_BRACET, string(1, c) };
    case '{':
        return { TokenType::L_BRACES, string(1, c) };
    case '}':
        return { TokenType::R_BRACES, string(1, c) };
    case '(':
        return { TokenType::L_PAREN, string(1, c) };
    case ')':
        return { TokenType::R_PAREN, string(1, c) };
    case '^':
        return { TokenType::EXP_OP, string(1, c) };
    case '=':
        return { TokenType::assign_op, string(1, c) };
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
            if (id == "float" || id == "int")
                return { TokenType::RESERVED_WORD, id };
            else if (id == "while")
                return { TokenType::WHILE, id };
            else if (id == "for")
                return { TokenType::FOR, id };
            else if (id == "if")
                return { TokenType::IF, id };
            else {
                return{ TokenType::IDENTIFIER,id};
            }
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
        cout << "Token(" << token.value << ", " << tokenTypeToString(token.type) << ")\n";
        if (token.type == TokenType::END) break;
    }

    return 0;
}
