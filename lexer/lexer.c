#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "lexer.h"
#include "tokens.h"

#define FALSE 0
#define TRUE 1

#define MATCH_N 1
#define REG_FLAGS 0
  
static regmatch_t match;
static TokenTypes char_tokens[256] = {0};
static TrieNode *trie = NULL;

Token *lex(const char *, int, int);

void init_char_tokens(void);

void init_keyword_trie(void);
void insert_keyword(TrieNode *root, const char *, TokenTypes);
TrieNode *create_trie_node(void);
TokenTypes match_keyword(TrieNode*, const char**, size_t*);
void parse_id(Token*, uint32_t*, const char**);
void parse_num(Token*, uint32_t*, const char**);


int32_t reg_check(regex_t *, const char *);

Token *lex_start(const char *str){
  init_char_tokens();
  init_keyword_trie();


  uint32_t size = 0;
  uint32_t capacity = (uint32_t) strlen(str) / 4 + 2;
  Token *tokens = malloc(capacity * sizeof(Token)); // Initial arbitrary size

  const char *cursor = str;

  while(*cursor){
    /* Reallocate tokens array if it isn't large enough */
    if(size >= capacity){
      capacity *= 2;
      tokens = realloc(tokens, capacity * sizeof(Token));
    }

    /* skip whitespaces */
    if(isspace(*cursor)) {
      while (*cursor && isspace(*cursor)) cursor++;
      continue;
    }

    /* single character tokens */
    if(char_tokens[(unsigned char)*cursor]){
      tokens[size++] = (Token) { .type = char_tokens[(unsigned char)*cursor] };
      cursor++;
      continue;
    }

    /* number literals */
    if(isdigit(*cursor) || (*cursor == '.' && isdigit(*(cursor + 1)))){
      parse_num(tokens, &size, &cursor);
    }

    /* other tokens non-literal */
    if(isalpha(*cursor) || *cursor == '_'){
      size_t word_len = 0;
      TokenTypes matched_type = match_keyword(trie, &cursor, &word_len);

      if(word_len){
        tokens[size++] = (Token) { .type = matched_type };
        cursor += word_len;
      }else{
        parse_id(tokens, &size, &cursor);
      }
      continue;
    }
  }

  if(size == capacity) tokens = realloc(tokens, (capacity + 1) * sizeof(Token));
  Token eof = { .type = TOK_EOF };
  tokens[size++] = eof;

  return tokens;
}

void init_keyword_trie(void){
  trie = create_trie_node(); // root

  /* ints */
  insert_keyword(trie, "i16", TOK_I16);
  insert_keyword(trie, "int16", TOK_I16);
  insert_keyword(trie, "i32", TOK_I32);
  insert_keyword(trie, "int32", TOK_I32);
  insert_keyword(trie, "I64", TOK_I64);
  insert_keyword(trie, "int64", TOK_I64);

  /* unsigned ints */
  insert_keyword(trie, "u16", TOK_U16);
  insert_keyword(trie, "uint16", TOK_U16);
  insert_keyword(trie, "u32", TOK_U32);
  insert_keyword(trie, "uint32", TOK_U32);
  insert_keyword(trie, "u64", TOK_U64);
  insert_keyword(trie, "uint64", TOK_U64);

  /* floats */
  insert_keyword(trie, "f32", TOK_F32);
  insert_keyword(trie, "float32", TOK_F32);
  insert_keyword(trie, "f64", TOK_F64);
  insert_keyword(trie, "float64", TOK_F64);
}

void insert_keyword(TrieNode *root, const char *key, TokenTypes token_type){
  TrieNode *curr_node = root;
  for(const char *p = key; *p; p ++){
    unsigned char c = (unsigned char)*p;
    if(!curr_node->children[c]) curr_node->children[c] = create_trie_node();
    curr_node = curr_node->children[c];
  }
  curr_node->token_type = token_type;
  curr_node->is_valid = TRUE;
}

TrieNode *create_trie_node(void){
  TrieNode *t_node = calloc(1, sizeof(TrieNode));
  t_node->token_type = 0;
  t_node->is_valid = FALSE;
  return t_node;
}

void init_char_tokens(void){
  memset(char_tokens, 0, sizeof(char_tokens)); // for defaults

  char_tokens[')'] = TOK_RPAREN;
  char_tokens['('] = TOK_LPAREN;
  char_tokens['}'] = TOK_RBRAC;
  char_tokens['{'] = TOK_LBRAC;
  char_tokens[','] = TOK_COMMA;
  char_tokens[';'] = TOK_SEMI;
  char_tokens[':'] = TOK_COLON;
  char_tokens['.'] = TOK_PERIOD;
  char_tokens['+'] = TOK_PLUS;
  char_tokens['-'] = TOK_DASH;
  char_tokens['/'] = TOK_SLASH;
  char_tokens['*'] = TOK_STAR;
  char_tokens['^'] = TOK_CARET;
}

TokenTypes match_keyword(TrieNode* root, const char** cursor, size_t* length) {
    TrieNode* current = root;
    const char* start = *cursor;
    const char* p = start;
    TokenTypes last_match = 0;
    size_t last_match_len = 0;
    
    while (*p && (isalnum(*p) || *p == '_')) {
        unsigned char c = (unsigned char)*p;
        if (!current->children[c]) break;
        current = current->children[c];
        p++;
        if (current->is_valid) {
            last_match = current->token_type;
            last_match_len = p - start;
        }
    }

    char next_char = *(start + last_match_len);
    if (last_match_len > 0 && (isalnum(next_char) || next_char == '_' || next_char == '\'')) {
        last_match = 0;
        last_match_len = 0;
    }

    *length = last_match_len;
    return last_match;
}


void parse_id(Token *tokens, uint32_t *size, const char **cursor){
  const char *start = *cursor;
  const char *p = start;

  /*   ^[a-zA-Z_][a-zA-Z0-9_']*   */
  if(isalpha(*p) || *p == '_'){
    p++;
    while(*p && (isalnum(*p) || *p == '_' || *p == '\'')){
      p++;
    }
  }

  size_t len = p - start;
  char *id_str = strndup(start, len);

  tokens[(*size)++] = (Token) { .type = TOK_ID, .data = id_str };
  *cursor = p;
}

void parse_num(Token *tokens, uint32_t *size, const char **cursor) {
    const char *start = *cursor;
    const char *p = start;

    int seen_digit = 0;
    int seen_dot = 0;

    if (*p == '.') {
        seen_dot = 1;
        p++;
        if (!isdigit(*p)) {
            tokens[(*size)++] = (Token){ .type = TOK_PERIOD };
            *cursor = p;
            return;
        }
        seen_digit = 1; // Because we will now parse digits after the dot
    }

    while (*p) {
        if (isdigit(*p)) {
            seen_digit = 1;
            p++;
        } else if (*p == '.' && !seen_dot) {
            seen_dot = 1;
            p++;
        } else {
            break;
        }
    }

    if (!seen_digit) {
        *cursor = p;
        return;
    }

    size_t len = p - start;
    char *num_str = strndup(start, len);

    tokens[(*size)++] = (Token){
        .type = TOK_LITERAL,
        .data = num_str
    };

    *cursor = p;
}

int32_t reg_check(regex_t *regexpr, const char *cursor){ return regexec(regexpr, cursor, MATCH_N, &match, REG_FLAGS) == 0; }