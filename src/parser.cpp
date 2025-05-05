#include "parser.hpp"

#include "compiler_msg.hpp"
#include "lexer.hpp"

namespace compiler
{

inline auto Parser::expect(const Token &token) -> void
{
    if (this->currentToken->type != token.type) {
        compiler::error("Expected {}, got {}",
                        compiler::TokenNames.at(token.type),
                        compiler::TokenNames.at(this->currentToken->type));
    }
}

auto Parser::parseTokens(const std::vector<Token> &tokens) -> void
{
    this->currentToken = &tokens[0];
    this->expect({TokenType::Identifier, "lul"});
}

} // namespace compiler