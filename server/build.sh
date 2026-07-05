#!/bin/bash
echo "Building P++ compiler for Linux..."
cd ../compiler
gcc -o p-plus-plus main.c lex.yy.c parser.tab.c ast.c semantic.c -lm
echo "Compiler built successfully"