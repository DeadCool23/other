#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "errs.h"

#include <stdbool.h>
#include <stddef.h>

bool is_opt(char* string);
err_t get_opts(int argc, char** argv, char** flags, size_t* flags_cnt);

#endif  // __OPTIONS_H__
