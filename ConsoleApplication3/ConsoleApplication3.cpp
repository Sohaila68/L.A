#include <iostream>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

enum Token {
    INT_LIT = 10,
    IDENT = 11,
    ASSIGN_OP = 20,
    ADD_OP = 21,
    SUB_OP = 22,
    MULT_OP = 23,
    DIV_OP = 24,
    LEFT_PAREN = 25,
    RIGHT_PAREN = 26,
    SEMICOLON = 27,
    EOF_TOKEN = -1
};

int charClass;
char nextChar;
string lexeme;
int lexLen;
Token nextToken;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

void addChar();
void getChar(stringstream& inputStream);
void getNonBlank(stringstream& inputStream);
Token lookup(char ch);
Token lex(stringstream& inputStream);

void addChar() {
    if (lexLen <= 98) {
        lexeme += nextChar;
        lexLen++;
    }
    else {
        cerr << "Error - lexeme is too long" << endl;
    }
}
void getChar(stringstream& inputStream) {
    nextChar = inputStream.get();
    if (inputStream.eof()) {
        charClass = EOF;
    }
    else if (isalpha(nextChar)) {
        charClass = LETTER;
    }
    else if (isdigit(nextChar)) {
        charClass = DIGIT;
    }
    else {
        charClass = UNKNOWN;
    }
}
void getNonBlank(stringstream& inputStream) {
    while (isspace(nextChar)) {
        getChar(inputStream);
    }
}
Token lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        return LEFT_PAREN;
    case ')':
        addChar();
        return RIGHT_PAREN;
    case '+':
        addChar();
        return ADD_OP;
    case '-':
        addChar();
        return SUB_OP;
    case '*':
        addChar();
        return MULT_OP;
    case '/':
        addChar();
        return DIV_OP;
    case '=':
        addChar();
        return ASSIGN_OP;
    case ';':
        addChar();
        return SEMICOLON;
    default:
        addChar();
        return EOF_TOKEN;
    }
}
Token lex(stringstream& inputStream) {
    lexLen = 0;
    lexeme.clear();
    getNonBlank(inputStream);

    switch (charClass) {
    case LETTER: 
        addChar();
        getChar(inputStream);
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar(inputStream);
        }
        nextToken = IDENT;
        break;

    case DIGIT:  
        addChar();
        getChar(inputStream);
        while (charClass == DIGIT) {
            addChar();
            getChar(inputStream);
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN: 
        nextToken = lookup(nextChar);
        getChar(inputStream);
        break;

    case EOF: 
        nextToken = EOF_TOKEN;
        lexeme = "EOF";
        break;

    default:
        nextToken = EOF_TOKEN;
        break;
    }

    cout << "Next token is: " << nextToken << " Next lexeme is " << lexeme << endl;
    return nextToken;
}

int main() {
  
    string input = "p = 8 * h + (3 / u);"; 
    
    stringstream inputStream(input);

    getChar(inputStream); 

    while (nextToken != EOF_TOKEN) {
        lex(inputStream);
    }

    return 0;
}
