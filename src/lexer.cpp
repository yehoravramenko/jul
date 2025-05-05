#include "lexer.hpp"
#include "compiler_msg.hpp"

#include <cctype>
#include <fstream>
#include <string>

constexpr std::string Keywords[] = {"return", "i32"};

namespace compiler
{

auto Lexer::getNextChar() -> void
{
    if (++this->filePos >= static_cast<int>(this->file.size())) {
        // compiler::error("Unexpected EOF");
        this->curChar = -1;
        return;
    }
    this->prevChar = this->curChar;
    this->curChar = this->file[this->filePos];
}

auto Lexer::stepBack() -> void
{
    this->curChar = this->file[--this->filePos];
    this->prevChar = this->file[this->filePos - 1];
}

auto Lexer::isKeyword(std::string_view Value) -> bool
{
    for (auto &k : ::Keywords) {
        if (Value == k)
            return true;
    }
    return false;
}

auto Lexer::getNextToken() -> void
{
    this->tokens.push_back(Token{});
    auto tok = &this->tokens.at(this->tokens.size() - 1);

    while (true) {
        do {
            this->getNextChar();
        } while (std::isspace(this->curChar));

        // TODO: Rewrite current character and next character
        if (this->curChar == '/' && this->file[filePos + 1] == '*') {
            do {
                this->getNextChar();
                if (this->curChar == -1) {
                    compiler::error("Expected */, got EOF (Did you forget to "
                                    "close a comment?)");
                }
            } while (!(this->prevChar == '*' && this->curChar == '/'));

            continue;
        }

        if (std::isalpha(this->curChar)) {
            std::string str{""};

            while (std::isalnum(this->curChar)) {
                str += this->curChar;
                this->getNextChar();
            }
            this->stepBack();
            tok->stringValue = str;
            tok->type = (Lexer::isKeyword(str)) ? TokenType::Keyword
                                                : TokenType::Identifier;

            return;
        }

        if (std::isdigit(this->curChar)) {
            std::string str{""};
            while (std::isdigit(this->curChar)) {
                str += this->curChar;
                this->getNextChar();
            }
            this->stepBack();
            tok->intValue = std::stoi(str);
            tok->type = TokenType::IntLit;

            return;
        }

        switch (this->curChar) {
        case ':':
            tok->type = TokenType::Colon;
            return;
        case ';':
            tok->type = TokenType::Semicolon;
            return;

        case '(':
            tok->type = TokenType::OpenParen;
            return;
        case ')':
            tok->type = TokenType::CloseParen;
            return;

        case '{':
            tok->type = TokenType::OpenCurly;
            return;
        case '}':
            tok->type = TokenType::CloseCurly;
            return;
        }

        // compiler::todo("Parse other tokens in the file");
        compiler::error("Unexpected character {}",
                        std::string(1, this->curChar));
    }
}

auto Lexer::debugTokens() -> void
{
    for (auto &tok : this->tokens) {
        compiler::log("TOKEN: {}", compiler::TokenNames.at(tok.type));
        if (tok.type == TokenType::Identifier ||
            tok.type == TokenType::Keyword) {
            compiler::log("\tVALUE: {}",
                          std::get<std::string>(tok.stringValue));
        }
    }
}

auto Lexer::tokenizeFile(std::string_view filepath) -> void
{
    // TODO: Handle errors during reading the file

    auto FStream = std::ifstream(filepath.data());
    auto FileSize = FStream.seekg(0, std::ios::end).tellg();
    this->file = std::string(FileSize, '\0');
    FStream.seekg(0);
    FStream.read(this->file.data(), FileSize);

    this->filePos = -1;
    this->curChar = '\0';
    this->prevChar = '\0';

    while (this->filePos < static_cast<int>(this->file.size()) - 1) {
        this->getNextToken();
    }
    this->debugTokens();
}

} // namespace compiler