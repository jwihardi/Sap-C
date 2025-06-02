#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "errors/errors.h"
#include "lexer/lexer.h"
#include "lexer/tokens.h"

void print_lexed_token(const Token);
char *file_to_string(const char *);
char *prepare_filename(char *);

int main(int argc, char *argv[]){

  Token *tokens = lex_start(file_to_string(prepare_filename(argv[1])));
  
  printf("[");
  int counter = 0;
  while(1){
    print_lexed_token(tokens[counter++]);
    if(tokens[counter].type == TOK_EOF) {
      print_lexed_token(tokens[counter]);
      break;
    }
  }

  printf("\n");
  return 0;
}

void print_lexed_token(const Token token){
  
  switch(token.type){
    case TOK_EOF: printf("TOK_EOF]"); break;
    case TOK_ID: printf("TOK_ID \"%s\"; ", (char *)token.data); break;
    case TOK_PLUS: printf("TOK_PLUS; "); break;
    case TOK_DASH: printf("TOK_DASH; "); break;
    case TOK_STAR: printf("TOK_STAR; "); break;
    case TOK_SLASH: printf("TOK_SLASH; "); break;
    case TOK_CARET: printf("TOK_CARET; "); break;
    case TOK_IF: printf("TOK_IF; "); break;
    case TOK_ELSE: printf("TOK_ELSE; "); break;
    case TOK_WHILE: printf("TOK_WHILE; "); break;
    case TOK_FOR: printf("TOK_FOR; "); break;
    case TOK_I16: printf("TOK_I16; "); break;
    case TOK_I32: printf("TOK_I32; "); break;
    case TOK_I64: printf("TOK_I64; "); break;
    case TOK_U16: printf("TOK_U16; "); break;
    case TOK_U32: printf("TOK_U32; "); break;
    case TOK_U64: printf("TOK_U64; "); break;
    case TOK_LITERAL: printf("TOK_LITERAL %s; ", (char *)token.data); break;
    case TOK_F32: printf("TOK_F32; "); break;
    case TOK_F64: printf("TOK_F64; "); break;
    case TOK_LPAREN: printf("TOK_LPAREN; "); break;
    case TOK_RPAREN: printf("TOK_RPAREN; "); break;
    case TOK_LBRAC: printf("TOK_LBRAC; "); break;
    case TOK_RBRAC: printf("TOK_RBRAC; "); break;
    case TOK_SEMI: printf("TOK_SEMI; "); break;
    case TOK_COLON: printf("TOK_COLON; "); break;
    case TOK_COMMA: printf("TOK_COMMA; "); break;
    case TOK_PERIOD: printf("TOK_PERIOD; "); break;
    case TOK_EQUAL: printf("TOK_EQUAL; "); break;
    case TOK_EQUALCMP: printf("TOK_EQUALCMP; "); break;
    case TOK_NOT: printf("TOK_NOT; "); break;
    case TOK_NOTEQUAL: printf("TOK_NOTEQUAL; "); break;
    case TOK_AND: printf("TOK_AND; "); break;
    case TOK_OR: printf("TOK_OR; "); break;
    case TOK_ARROW: printf("TOK_ARROW; "); break;
    case TOK_LESS: printf("TOK_LESS; "); break;
    case TOK_GREATER: printf("TOK_GREATER; "); break;
    case TOK_LESSEQ: printf("TOK_LESSEQ; "); break;
    case TOK_GREATEREQ: printf("TOK_GREATEREQ; "); break;
    case TOK_CLASS: printf("TOK_CLASS; "); break;
    case TOK_PUBLIC: printf("TOK_PUBLIC; "); break;
    case TOK_PRIVATE: printf("TOK_PRIVATE; "); break;
    case TOK_PLUSCOMP: printf("TOK_PLUSCOMP; "); break;
    case TOK_STARCOMP: printf("TOK_STARCOMP; "); break;
    case TOK_SLASHCOMP: printf("TOK_SLASHCOMP; "); break;
    case TOK_DASHCOMP: printf("TOK_DASHCOMP; "); break;
    case TOK_AT: printf("TOK_AT; "); break;
    default: printf("ERROR"); break;
  }
  return;
}

char *file_to_string(const char *filename){
  
  FILE *file = fopen(filename, "rb"); // Read in binary mode

  fseek(file, 0, SEEK_END);
  
  uint64_t len = ftell(file);

  rewind(file);

  char *buffer = malloc(len + 1);
  fread(buffer, 1, len, file);
  buffer[len] = '\0';

  fclose(file);

  return buffer;
}

char *prepare_filename(char *str){
  while(isspace((unsigned char)*str)) str++;

  char *end = str + strlen(str) - 1;
  while(isspace((unsigned char)*str) && end > str){
    *end = '\0';
    end--;
  }
  return str;
}