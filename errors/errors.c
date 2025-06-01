#include "errors.h"
#include <string.h>
#include <stdio.h>



void print_argument_errors(const char *e){
  if(strcmp(e, "no arg") == 0){
    printf("missing file");
  }

}

void print_lexer_error(const char *e){return;}

void print_parser_error(const char *e){return;}












