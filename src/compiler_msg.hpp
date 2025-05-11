#pragma once
#include <format>
#include <string_view>

namespace compiler
{

auto log(std::string_view msg) -> void;
auto warning(std::string_view msg) -> void;
auto error(std::string_view msg) -> void;
auto todo(std::string_view msg) -> void;

} // namespace compiler