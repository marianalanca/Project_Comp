#include "symbol_table.h"

int check_program(is_program* p);
int check_vardec_list(is_vardec_list* ivl);
int check_vardec(is_vardec* iv);
int check_integer_dec(is_integer_dec* iid);
int check_character_dec(is_character_dec* icd);
int check_double_dec(is_double_dec* idd);
int check_statement_list(is_statement_list* isl);
int check_statement(is_statement* is);
int check_write_statement(is_write_statement* iws);