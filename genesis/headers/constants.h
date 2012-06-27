#pragma once
#include <stdio.h>

#define DEBUG 1

#if DEBUG == 1
#define print(x) fprintf(stdout, x)
#define printErr(x) fprintf(stderr, x)
#else
#define print(x)
#define printErr(x)
#endif

const int RESOLUTION [2] = {640, 480};