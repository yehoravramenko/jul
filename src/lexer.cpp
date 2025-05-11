#include "lexer.hpp"
#include "compiler_msg.hpp"

#include <cctype>
#include <fstream>
#include <string>

constexpr std::string Keywords[] = {"return", "i32"};

namespace compiler
{

auto Lexer::get_next_char() -> void
{
    if (++this->file_pos >= static_cast<int>(this->file.size())) {
        // compiler::error("Unexpected EOF");
        this->cur_char = -1;
        return;
    }
    this->prev_char = this->cur_char;
    this->cur_char = this->file[this->file_pos];
}

auto Lexer::step_back() -> void
{
    this->cur_char = this->file[--this->file_pos];
    this->prev_char = this->file[this->file_pos - 1];
}

auto Lexer::is_keyword(std::string_view Value) -> bool
{
    for (auto &k : ::Keywords) {
        if (Value == k)
            return true;
    }
    return false;
}

auto Lexer::get_next_token() -> void
{
    this->tokens.push_back(Token{});
    const auto tok = &this->tokens.at(this->tokens.size() - 1);

    while (true) {
        do {
            this->get_next_char();
        } while (std::isspace(this->cur_char));

        // TODO: Rewrite current character and next character
        if (this->cur_char == '/' && this->file[file_pos + 1] == '*') {
            do {
                this->get_next_char();
                if (this->cur_char == -1) {
                    compiler::error("Expected */, got EOF (Did you forget to "
                                    "close a comment?)");
                }
            } while (!(this->prev_char == '*' && this->cur_char == '/'));

            continue;
        }

        if (std::isalpha(this->cur_char)) {
            std::string str{""};

            while (std::isalnum(this->cur_char)) {
                str += this->cur_char;
                this->get_next_char();
            }
            this->step_back();
            tok->string_value = str;
            tok->type = (Lexer::is_keyword(str)) ? TokenType::Keyword
                                                 : TokenType::Identifier;

            return;
        }

        if (std::isdigit(this->cur_char)) {
            std::string str{""};
            while (std::isdigit(this->cur_char)) {
                str += this->cur_char;
                this->get_next_char();
            }
            this->step_back();
            tok->int_value = std::stoi(str);
            tok->type = TokenType::IntLit;

            return;
        }

        switch (this->cur_char) {
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

        compiler::error(std::format("Unexpected character {}",
                                    std::string(1, this->cur_char)));
    }
}

auto Lexer::debug_tokens() -> void
{
    for (auto &tok : this->tokens) {
        compiler::log(
            std::format("TOKEN: {}", compiler::TokenNames.at(tok.type)));
        if (tok.type == TokenType::Identifier ||
            tok.type == TokenType::Keyword) {
            compiler::log(std::format("\tVALUE: {}",
                                      std::get<std::string>(tok.string_value)));
        }
    }
}

auto Lexer::tokenize_file(std::string_view filepath) -> void
{
    // TODO: Handle errors during reading the file

    auto fstream = std::ifstream(filepath.data());
    auto file_size = fstream.seekg(0, std::ios::end).tellg();
    this->file = std::string(file_size, '\0');
    fstream.seekg(0);
    fstream.read(this->file.data(), file_size);

    this->file_pos = -1;
    this->cur_char = '\0';
    this->prev_char = '\0';

    while (this->file_pos < static_cast<int>(this->file.size()) - 1) {
        this->get_next_token();
    }
    // this->debugTokens();
}

} // namespace compiler