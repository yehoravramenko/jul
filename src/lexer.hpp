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
    std::variant<std::string, int> stringValue, intValue;

    Token() = default;
    Token(const TokenType t, std::string_view s)
        : type(t), stringValue(s.data()) {};
    Token(const TokenType t, int i) : type(t), intValue(i) {};
};

class Lexer
{
  public:
    auto tokenizeFile(std::string_view filepath) -> void;

    auto getTokensList() -> std::vector<Token> & { return this->tokens; };

  private:
    auto getNextChar() -> void;
    auto stepBack() -> void;
    static auto isKeyword(std::string_view value) -> bool;

    auto getNextToken() -> void;

    auto debugTokens() -> void;

    std::string file;
    int filePos;

    // TODO: Write line number and its offset in error message
    // size_t FileLine;
    // size_t FileLineOffset;

    char curChar;
    char prevChar;

    std::vector<Token> tokens;
};

} // namespace compiler