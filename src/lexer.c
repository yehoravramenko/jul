#include "lexer.h"

#include <stdio.h>

static char current_char = 0;

enum TokenType {
  TOK_NULL = -1,
};

typedef struct {
  TokeType type;
} Token;

void lex_lexer(const char *filepath) {
  FILE *file = NULL;
  int c = 0;

  file = fopen(filepath, "r");
  if (file == NULL) {
    perror("Failed to open file");
  }
  while ((current_char = fgetc(file)) != EOF) {
    printf("%c", current_char);
  }
}
