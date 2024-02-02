#include <iostream>

#include "errs.h"
#include "zipper.hpp"
#include "unzipper.hpp"
#include "get_options.hpp"

int main(int argc, char **argv) {
    errs_t err = OK;
    int correct_opts;
    Options opts = Options(argc, argv, &correct_opts);
    if (correct_opts) {
        if (opts.help) {
            opts.helper(argv[0]);
        } else if (opts.unzip) {
            err = (errs_t)unzipper(opts);
        } else if (opts.zip) {
            err = (errs_t)zipper(opts);
        }
    } else err = ERR_ARGS;
    if (err == ERR_FILE) std::cout << "ERROR: Incorrect file" << std::endl;
    return err;
}