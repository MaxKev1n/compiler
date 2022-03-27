#include "header.h"
#include "lexer.h"
#include "convert.h"
using namespace std;

int main(){
    lexer l;
    l.run("../simulation/grammar.txt", "../simulation/test.txt");
    return 0;
}
