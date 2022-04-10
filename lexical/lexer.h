#pragma once
#include "header.h"

using namespace std;

struct chType{
    public:
        int id;
        string name;
        
        chType(int i, string n) : id(i), name(n){}
        chType(){};

        bool operator==(const chType &right){
            return this->id == right.id;
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

struct lexer
{
    public:
        static chType chtypeDetect(char ch);
        void run(string address_grammar, string address_txt, string address_output);
    private:
        string typeRecognition(string str);
        
};

struct Tuple{
    public:
        int line;
        string str;
        string type;
        Tuple();
        Tuple(int line, string str, string type) : line(line), str(str), type(type){};
};

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