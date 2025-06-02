#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
  TOK_ID,                     //  some string
  TOK_PLUS,                   //  +
  TOK_PLUSCOMP,               //  +=
  TOK_DASH,                   //  -
  TOK_DASHCOMP,               //  -=
  TOK_STAR,                   //  *
  TOK_STARCOMP,               //  *=
  TOK_SLASH,                  //  /
  TOK_SLASHCOMP,              //  /=
  TOK_CARET,                  //  ^
  TOK_EQUAL,                  //  =
  TOK_LESS,                   //  <
  TOK_GREATER,                //  >
  TOK_LESSEQ,                 //  <=
  TOK_GREATEREQ,              //  >=
  TOK_NOTEQUAL,               //  != 
  TOK_NOT,                    //  ! or not
  TOK_EQUALCMP,               //  == 
  TOK_AND,                    //  &&
  TOK_OR,                     //  ||
  TOK_ARROW,                  //  ->
  TOK_COMMENT,                //  //
  TOK_IF,                     //  if
  TOK_ELSE,                   //  else
  TOK_WHILE,                  //  while
  TOK_FOR,                    //  for
  TOK_BREAK,                  //  break
  TOK_CONTINUE,               //  continue
  TOK_I16,                    //  *i-16*
  TOK_I32,                    //  *i-32*
  TOK_I64,                    //  *i-64*
  TOK_U16,                    //  *u-16*
  TOK_U32,                    //  *u-32*
  TOK_U64,                    //  *u-64*
  TOK_F32,                    //  *f-32*
  TOK_F64,                    //  *f-64*
  TOK_LITERAL,                //  any value
  TOK_CHAR,                   //  *char*
  TOK_STRING,                 //  *string*
  TOK_RPAREN,                 //  )
  TOK_LPAREN,                 //  (
  TOK_RBRAC,                  //  }
  TOK_LBRAC,                  //  {
  TOK_RSBRAC,                 //  ]
  TOK_LSBRAC,                 //  [
  TOK_SEMI,                   //  ;
  TOK_COLON,                  //  :
  TOK_COMMA,                  //  ,
  TOK_PERIOD,                 //  .
  TOK_AT,                     //  @
  TOK_VOID,                   //  void
  TOK_RETURN,                 //  return
  TOK_SWITCH,                 //  switch
  TOK_CLASS,                  //  class
  TOK_PUBLIC,                 //  public
  TOK_PRIVATE,                //  private
  _TOK_LENGTH,                /* ----------------------------------- */
  TOK_EOF,                    //  EOF

} TokenType;

typedef struct {
  TokenType type;
  union{
    void *data;
  };
} Token;









#endif
