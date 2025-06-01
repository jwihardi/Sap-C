#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
  TOK_ID,                     //  some string
  TOK_PLUS,                   //  *
  TOK_DASH,                   //  -
  TOK_STAR,                   //  *
  TOK_SLASH,                  //  /
  TOK_CARET,                  //  ^
  TOK_IF,                     //  if
  TOK_ELSE,                   //  else
  TOK_WHILE,                  //  while
  TOK_FOR,                    //  for
  TOK_I16,                    //  *i-16*
  TOK_I32,                    //  *i-32*
  TOK_I64,                    //  *i-64*
  TOK_U16,                    //  *u-16*
  TOK_U32,                    //  *u-32*
  TOK_U64,                    //  *u-64*
  TOK_F32,                    //  *f-32*
  TOK_F64,                    //  *f-64*
  TOK_LITERAL,            //  any value
  TOK_CHAR,                   //  *char*
  TOK_STRING,                 //  *string*
  TOK_RPAREN,                 //  )
  TOK_LPAREN,                 //  (
  TOK_RBRAC,                  //  }
  TOK_LBRAC,                  //  {
  TOK_SEMI,                   //  ;
  TOK_COLON,                  //  :
  TOK_COMMA,                  //  ,
  TOK_PERIOD,                 //  .
  _TOK_LENGTH,                /* ----------------------------------- */
  TOK_EOF,                    //  EOF

} TokenTypes;

typedef struct {
  TokenTypes type;
  union{
    void *data;
  };
} Token;









#endif
