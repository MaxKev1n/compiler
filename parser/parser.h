#ifndef _PARSER_H
#define _PARSER_H
#include "header.h"
using namespace std;

struct NonTerminal
{
    private:
        int id;
        set<chType> firstUnion;

    public:
        bool operator==(const NonTerminal &right) { return this->id == right.id; }
        void addFirstUnion(chType terminal) { this->firstUnion.insert(terminal); }
        void setId(int id) { this->id = id; }
        int firstUnionCount() { return this->firstUnion.size(); }
};

struct chType{
    public:
        int id;
        string name;
        NonTerminal nonTerminal;
        
        chType(int i, string n) : id(i), name(n){}
        chType(){};
        chType(int i) : id(24), name("nonTerminal") { this->nonTerminal.setId(i); }

        bool operator==(const chType &right){
            return this->id == right.id;
        }

        bool operator!=(const chType &right){
            return this->id != right.id;
        }
};

const chType letter(0, "letter");
const chType natNumber(1, "natNumber");
const chType underline(2, "underline");
const chType midLeftPar(3, "midLeftPar");
const chType midRightPar(4, "midRightPar");
const chType Plus(5, "Plus");
const chType Minus(6, "Minus");
const chType logAnd(7, "logAnd");
const chType logOr(8, "logOr");
const chType logNot(9, "logNot");
const chType logXor(10, "logXor");
const chType rightArrow(11, "rightArrow");
const chType leftArrow(12, "leftArrow");
const chType semicolon(13, "semicolon");
const chType multi(14, "multi");
const chType smallLeftPar(15, "smallLeftPar");
const chType smallRightPar(16, "smallRightPar");
const chType dollar(17, "dollar");
const chType epsilon(18, "epsilon");
const chType dot(19, "dot");
const chType letter_E(20, "letter_E");
const chType letter_i(21, "letter_i");
const chType space(22, "space");
const chType zero(23, "zero");
const chType nonTerminal(24, "nonTerminal");

const set<char> let {'a','b','c','d','e','f','g','h','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const set<char> natNum {'1','2','3','4','5','6','7','8','9'};

static vector<chType> chTypeList {letter, natNumber, underline, midLeftPar, midRightPar, Plus, Minus, logAnd, logOr,
                           logNot, logXor, rightArrow, leftArrow, semicolon, multi, smallLeftPar,smallRightPar,
                           dollar, epsilon, dot, letter_E, letter_i, space, zero};

const set<string> keyword {"define", "switch", "iwire", "owire", "oreg", "wire", "reg", "mod", "default",
                            "case", "if", "else", "elseif"};

const set<string> qualifier {"abstract", "public", "private", "override", "const"};

const set<string> operators {"[", "]", "+", "-", "&", "|", "~", "^", ">>", "<<", ">>>", "(", ")", "*", "<", ">"};

const set<chType> terminalList {};

struct Tuple{
    private:
        int line;
        string str;
        string type;
    public:
        Tuple();
        Tuple(int line, string str, string type) : line(line), str(str), type(type){};

        int getLine() { return this->line; }
        string getStr() { return this->str; }
        string getType() { return this->type; }

        void setLine(int line) { this->line = line; }
        void setStr(string str) { this->str = str; }
        void setType(string type) { this->type = type; }
};

struct Grammar
{
    private:
        chType left;
        vector<chType> right;

    public:
        chType getLeft() { return this->left; }
        chType getRight(int index) { return this->right[index]; }
        vector<chType> getRightList() { return this->right; }

        void setLeft(int i) { this->left = chType(i); }
        void addRight(chType ch) { this->right.push_back(ch); }
};

struct Parser
{
    private:
        vector<Grammar> grammarList;
        vector<chType> nonTerminalList;
        
    public:
        void readGrammar(string addr);
        void getFirstUnion();
        bool breakFistUnion(vector<int> count);
        vector<chType> getFirstUnion(Grammar grammar, int index); //calculate grammar's FirstUnion
};


#endif