#include "compiler_msg.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <string>
#include <string_view>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

auto main(int argc, char **argv) -> int
{
    if (argc < 2) {
        compiler::error("No file specified.\n\n"
                        "Usage: jul [target](.jul) <options>");
    }

    std::vector<std::string> source_files = {};

    for (auto i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            auto f = std::string(argv[i]);
            if (!f.ends_with(".jul")) {
                f += ".jul";
            }
            if (!fs::exists(f)) {
                compiler::error(
                    std::format("Could not find file {}", std::string_view(f)));
            }
            source_files.push_back(f);
        } else {
            compiler::todo("Parse compiler options");
        }
    }

    compiler::Lexer lexer{};
    lexer.tokenize_file(source_files[0]);

    compiler::Parser parser{};
    parser.parse_tokens(lexer.get_tokens_list());

    return 0;
}