#pragma once
#include "lexer.hpp"

#include <vector>

namespace compiler
{

class Parser
{
  public:
    auto parseTokens(const std::vector<Token> &tokens) -> void;

  private:
    const Token *currentToken = nullptr;

    inline auto expect(const Token &token) -> void;

    // auto expectType(const Token &tokens) -> void;
    // auto expectValue(const Token &tokens) -> void;
};

} // namespace compiler