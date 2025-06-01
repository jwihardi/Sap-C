#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"

Token *lex_start(const char *);

typedef struct TrieNode {
    struct TrieNode *children[256];
    TokenTypes token_type;
    int is_valid;
} TrieNode;

#endif
