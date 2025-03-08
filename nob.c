#define NOB_IMPLEMENTATION
#include "nob.h"

#define EXE_NAME "jul"

#define SRC_DIR "src/"
#define BUILD_DIR "build/"
#define BIN_DIR BUILD_DIR "bin/"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "-o", BIN_DIR EXE_NAME,
                 SRC_DIR "main.c", SRC_DIR "lexer.c");
  nob_mkdir_if_not_exists(BUILD_DIR);
  nob_mkdir_if_not_exists(BIN_DIR);
  if (!nob_cmd_run_sync(cmd))
    return 1;
  return 0;
}
