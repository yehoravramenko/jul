#pragma once
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

constexpr std::string TTYPE_DBG[] = {
    "Identifier", "Keyword",    "IntLit", "OpenCurly", "CloseCurly",
    "OpenParen",  "CloseParen", "Colon",  "Semicolon",
};

struct Token {
    TokenType type;
    std::variant<std::string, int> stringValue, intValue;
};

class Lexer
{
  public:
    Lexer(std::string_view filepath);
    auto tokenizeFile() -> void;

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