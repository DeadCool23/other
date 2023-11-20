#ifndef __FILEOUT_H__
#define __FILEOUT_H__

#include <stdio.h>

#include "errs.h"

err_t print_file(const char *file_name, const char *flags, size_t *lines_cnt);

#endif  // __FILEOUT_H__
