#!/bin/sh

# run lex and compile the resulting C analyser
lex uccompiler.l
yacc -d uccompiler.y --debug
cc -o $1 y.tab.c lex.yy.c

# 'lex' and 'gcc' are commonly available too