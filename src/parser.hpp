#pragma once
#include "lexer.hpp"

#include <vector>

namespace compiler
{

class Parser
{
  public:
    auto parse_tokens(const std::vector<Token> *tokens) -> void;

  private:
    const std::vector<Token> *tokens = nullptr;
    const Token *current_token = nullptr;
    int token_index = 0;

    auto expect(const TokenType type) -> void;
    auto get_and_expect(const TokenType type) -> void;
};

} // namespace compiler