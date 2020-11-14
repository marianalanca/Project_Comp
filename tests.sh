#!/bin/sh

# run lex and compile the resulting C analyser

bash yacc.sh uccompiler

for file in meta2/*
do
    printf "$file\n"
    ./uccompiler < "$file" > "test.out"
done

# 'lex' and 'gcc' are commonly available too