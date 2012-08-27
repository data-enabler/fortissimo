#pragma once
#include <stdio.h>
#include "constants.h"

#ifdef DEBUG
#define print(x) fprintf(stdout, x)
#define printErr(x) fprintf(stderr, x)
#else
#define print(x)
#define printErr(x)
#endif

bool safeInit(const char* name, bool (*func) (void));