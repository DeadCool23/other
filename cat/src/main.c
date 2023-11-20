#include <stdlib.h>
#include <string.h>

#include "fileout.h"
#include "options.h"

int main(int argc, char **argv) {
    err_t err = OK;
    char *flags = "";
    size_t flags_cnt = 0;
    size_t lines_cnt = 0;
    err = get_opts(argc, argv, &flags, &flags_cnt);
    for (int i = 1 + flags_cnt; i < argc && !err; i++) err = print_file(argv[i], flags, &lines_cnt);

    if (!err && !(argc - flags_cnt - 1)) err = print_file("-", flags, &lines_cnt);

    if (strlen(flags)) free(flags);
    return err;
}
