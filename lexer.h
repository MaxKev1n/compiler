#ifndef LEXER_H
#define LEXER_H
#include "header.h"

const set<const char> let {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                         'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const set<const char> num {'0','1','2','3','4','5','6','7','8','9'};

struct chType{
    public:
        int id;
        
        chType(int i) : id(i){}

        bool operator==(const chType &right){
            return this->id == right.id;
        }
};

chType letter(0);
chType number(1);
chType underline(2);
chType midLeftPar(3);
chType midRightPar(4);
chType Plus(5);
chType Minus(6);
chType logAnd(7);
chType logOr(8);
chType logNot(9);
chType logXor(10);
chType rightArrow(11);
chType leftArrow(12);
chType semicolon(13);
chType multi(14);
chType smallLeftPar(15);
chType smallRightPar(16);
chType dollar(17);
chType epsilon(18);

struct lexer
{
    public:
        static chType chtypeDetect(char ch);
    private:
        
};


#endif