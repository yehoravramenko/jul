#pragma once
#include <string>
#include <string_view>

namespace compiler
{

enum class TokenType {
    Eof = -1,

    Id = 0,
    Keyword,
    IntLit,

    OpenCurly,
    CloseCurly,

    OpenParen,
    CloseParen,

    Colon,
    Semicolon,
};

class Lexer
{
  public:
    Lexer(std::string_view Filepath);
    auto getNextToken() -> void;

  private:
    auto getNextChar() -> void;

    std::string CurrentFile;
    size_t FilePos;

    char CurChar;
    char PrevChar;

    TokenType CurrentToken;

    int IntLitValue;
    std::string Identifier;
};

} // namespace compiler