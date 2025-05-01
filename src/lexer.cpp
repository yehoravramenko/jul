#include "lexer.hpp"
#include "compiler_msg.hpp"

#include <fstream>
#include <string>

namespace compiler
{

Lexer::Lexer(std::string_view Filepath)
{
    // TODO: Handle errors during reading the file

    auto FStream = std::ifstream(Filepath.data());
    auto FileSize = FStream.seekg(0, std::ios::end).tellg();
    this->CurrentFile = std::string(FileSize, '\0');
    FStream.seekg(0);
    FStream.read(this->CurrentFile.data(), FileSize);

    compiler::log(this->CurrentFile);
    this->FilePos = -1;
    this->CurChar = '\0';
    this->PrevChar = '\0';
}

auto Lexer::getNextChar() -> void
{
    if (++this->FilePos >= this->CurrentFile.size()) {
        compiler::error("Unexpected EOF");
    }
    this->PrevChar = this->CurChar;
    this->CurChar = this->CurrentFile[this->FilePos];
}

auto Lexer::getNextToken() -> void
{
    while (true) {
        do {
            this->getNextChar();
        } while (std::isspace(this->CurChar));

        if (this->PrevChar == '/' && this->CurChar == '*') {
            while (!(this->PrevChar == '*' && this->CurChar == '/')) {
                getNextChar();
            }
        }
        compiler::todo("Parse other tokens in file");
    }
}

} // namespace compiler