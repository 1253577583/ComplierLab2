bison -d syntax.y
flex lexical.l
gcc main.c syntax.tab.c node.c semantic.c -lfl -ly -o parser
