#include "parser.hpp"

#include "compiler_msg.hpp"
#include "lexer.hpp"

namespace compiler
{

auto Parser::expect(const TokenType type) -> void
{
    if (this->current_token->type != type) {
        compiler::error(
            std::format("Expected {}, got {}", compiler::TokenNames.at(type),
                        compiler::TokenNames.at(this->current_token->type)));
    }
}

auto Parser::get_and_expect(const TokenType type) -> void
{
    this->current_token = tokens[++this->token_index].data();
    this->expect(type);
}

auto Parser::parse_tokens(const std::vector<Token> *tokens) -> void
{
    this->tokens = tokens;
    this->current_token = tokens[0].data();

    this->expect(TokenType::Identifier);
}

} // namespace compiler