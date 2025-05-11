#include "compiler_msg.hpp"

#define FMT_HEADER_ONLY
#include <fmt/base.h>
#include <fmt/color.h>

enum class MsgKind {
    Log = 0,
    Warning,
    Error,
    Todo,
};

static auto printer(const MsgKind kind, std::string_view msg) -> void
{
    switch (kind) {
    case MsgKind::Error:
        fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "error: ");
        break;
    case MsgKind::Warning:
        fmt::print(fmt::emphasis::bold | fg(fmt::color::yellow), "warning: ");
        break;
    case MsgKind::Todo:
        fmt::print(fmt::emphasis::bold | fg(fmt::color::magenta), "todo: ");
        break;
    default:
        break;
    }

    fmt::println("{}", msg);
}

namespace compiler
{

auto log(std::string_view msg) -> void
{
    ::printer(MsgKind::Log, msg);
}

auto warning(std::string_view msg) -> void
{
    ::printer(MsgKind::Warning, msg);
}

auto error(std::string_view msg) -> void
{
    ::printer(MsgKind::Error, msg);
    std::exit(1);
}

auto todo(std::string_view msg) -> void
{
    ::printer(MsgKind::Todo, msg);
    std::exit(1);
}
} // namespace compiler