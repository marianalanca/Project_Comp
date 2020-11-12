#!/bin/sh

# run lex and compile the resulting C analyser

bash yacc.sh uccompiler

for file in meta2/*
do
    ./uccompiler < "$file" > "$file.out"
done

# 'lex' and 'gcc' are commonly available too