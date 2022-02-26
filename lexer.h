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
const chType number(1, "number");
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

struct lexer
{
    public:
        static chType chtypeDetect(char ch);
        void run(string address_grammar, string address_txt);
    private:
        
};

const set<char> let {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const set<char> num {'0','1','2','3','4','5','6','7','8','9'};

static vector<chType> chTypeList {letter, number, underline, midLeftPar, midRightPar, Plus, Minus, logAnd, logOr,
                           logNot, logXor, rightArrow, leftArrow, semicolon, multi, smallLeftPar,smallRightPar,
                           dollar, epsilon};