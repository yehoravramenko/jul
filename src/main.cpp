#include "compiler_msg.hpp"
#include "lexer.hpp"

#include <string>
#include <vector>

#include <filesystem>
namespace fs = std::filesystem;

auto main(int argc, char **argv) -> int
{
    if (argc < 2) {
        compiler::error("No file specified.\n\n"
                        "Usage: jul [target](.jul) <options>");
    }

    std::vector<std::string> SourceFiles = {};

    for (auto i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            auto f = std::string(argv[i]);
            if (!f.ends_with(".jul")) {
                f += ".jul";
            }
            if (!fs::exists(f)) {
                compiler::error("Could not find file " + f);
            }
            SourceFiles.push_back(f);
        } else {
            compiler::todo("Parse compiler options");
        }
    }

    compiler::Lexer Lexer{SourceFiles[0]};
    Lexer.getNextToken();
    return 0;
}