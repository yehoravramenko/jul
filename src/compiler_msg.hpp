#pragma once

#define FMT_HEADER_ONLY
#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>

#include <cstdlib>
#include <utility>

namespace compiler
{

enum class LogKind {
    Log = 0,
    Warning,
    Error,
    Todo,
};

template <typename... Args>
auto msg(const LogKind kind, std::string_view format, Args &&...args) -> void
{
    switch (kind) {
    case LogKind::Error:
        fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "error: ");
        break;
    case LogKind::Warning:
        fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "warning: ");
        break;
    case LogKind::Todo:
        fmt::print(fmt::emphasis::bold | fg(fmt::color::magenta), "todo: ");
        break;
    default:
        break;
    }

    fmt::vprint(format, fmt::make_format_args(args...));
    fmt::println("");
}

template <typename... Args>
auto log(std::string_view format, Args &&...args) -> void
{
    compiler::msg(LogKind::Log, format, std::forward<Args>(args)...);
}

template <typename... Args>
auto warning(std::string_view format, Args &&...args) -> void
{
    compiler::msg(LogKind::Warning, format, std::forward<Args>(args)...);
}

template <typename... Args>
auto error(std::string_view format, Args &&...args) -> void
{
    compiler::msg(LogKind::Error, format, std::forward<Args>(args)...);
    std::exit(1);
}

template <typename... Args>
auto todo(std::string_view format, Args &&...args) -> void
{
    compiler::msg(LogKind::Todo, format, std::forward<Args>(args)...);
    std::exit(1);
}

} // namespace compiler
