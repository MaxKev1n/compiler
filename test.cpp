#include "header.h"
using namespace std;

int main(){
    lexer l;
    l.run("/home/czh/compiler/grammar.txt", "/home/czh/compiler/test.txt");
    return 0;
}