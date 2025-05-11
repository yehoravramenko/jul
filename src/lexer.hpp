#pragma once
#include "frozen/unordered_map.h"

#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace compiler
{

enum class TokenType {
    Eof = -1,

    Identifier = 0,
    Keyword,
    IntLit,

    OpenCurly,
    CloseCurly,

    OpenParen,
    CloseParen,

    Colon,
    Semicolon,
};

constexpr frozen::unordered_map<TokenType, std::string_view, 9> TokenNames = {
    {TokenType::Identifier, "identifier"},
    {TokenType::Keyword, "keyword"},
    {TokenType::IntLit, "int literal"},
    {TokenType::OpenCurly, "open curly bracket"},
    {TokenType::CloseCurly, "close curly bracket"},
    {TokenType::OpenParen, "open parenthesis"},
    {TokenType::CloseParen, "close parenthesis"},
    {TokenType::Colon, "colon"},
    {TokenType::Semicolon, "semicolon"},
};

struct Token {
    TokenType type;
    std::variant<std::string, int> string_value, int_value;

    Token() = default;
    Token(const TokenType t, std::string_view s)
        : type(t), string_value(s.data()) {};
    Token(const TokenType t, int i) : type(t), int_value(i) {};
};

class Lexer
{
  public:
    auto tokenize_file(std::string_view filepath) -> void;

    auto get_tokens_list() -> std::vector<Token> * { return &this->tokens; };

  private:
    auto get_next_char() -> void;
    auto step_back() -> void;
    static auto is_keyword(std::string_view value) -> bool;

    auto get_next_token() -> void;

    auto debug_tokens() -> void;

    std::string file;
    int file_pos;

    // TODO: Write line number and its offset in error message
    // size_t FileLine;
    // size_t FileLineOffset;

    char cur_char;
    char prev_char;

    std::vector<Token> tokens;
};

} // namespace compiler