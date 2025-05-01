#pragma once
#include <string_view>

namespace compiler
{
auto error(std::string_view Msg) -> void;
auto warning(std::string_view Msg) -> void;
auto msg(std::string_view Msg) -> void;
} // namespace compiler