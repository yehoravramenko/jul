#include "compiler_msg.hpp"

#include <cstdlib>
#include <print>
#include <string>

enum class TextColor {
    Normal = 39,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Magenta = 35,
};

enum class TextStyle {
    Normal = 0,
    Bold = 1,
};

static auto colorize(const TextColor Color,
                     const TextStyle Style = TextStyle::Normal)
    -> const std::string
{
    return "\x1b[" + std::to_string(static_cast<int>(Style)) + ";" +
           std::to_string(static_cast<int>(Color)) + "m";
}

static auto printLog(std::string_view Msg, std::string_view Header = "") -> void
{
    if (Header == "") {
        std::println("{}", Msg);
    } else {
        std::println("{}: {}", Header.data(),
                     ::colorize(TextColor::Normal) + Msg.data());
    }
}

namespace compiler
{

auto error(std::string_view Msg) -> void
{
    ::printLog(Msg, ::colorize(TextColor::Red, TextStyle::Bold) + "error");
    std::exit(1);
}

auto warning(std::string_view Msg) -> void
{
    ::printLog(Msg, ::colorize(TextColor::Yellow, TextStyle::Bold) + "warning");
}

auto log(std::string_view Msg) -> void
{
    ::printLog(Msg);
}

auto todo(std::string_view Msg) -> void
{
    ::printLog(Msg, ::colorize(TextColor::Magenta, TextStyle::Bold) + "todo");
    std::exit(1);
}

} // namespace compiler