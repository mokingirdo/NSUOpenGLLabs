﻿#include "Directory.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


bool Directory::Exists(const char * path)
{
    struct stat info;

    if (stat( path, &info ) != 0)
        return 0;
    else if (info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}
