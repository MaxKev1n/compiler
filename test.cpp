#include "header.h"
#include "lexer.h"
#include "convert.h"
using namespace std;

int main(){
    lexer l;
    l.run("/home/czh/compiler/simulation/grammar.txt", "/home/czh/compiler/simulation/test.txt");
    return 0;
}
