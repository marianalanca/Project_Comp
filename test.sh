bash yacc.sh uccompiler
for file in meta3/*
do
    filename=$(basename -- "$file")
    filename="${filename%.*}"
    printf "$filename\n"
    ./uccompiler -s < "$file" > "meta3/testes/$filename.out"
done