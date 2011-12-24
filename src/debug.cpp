#include "debug.h"

#include <cstdio>
#include <cstdlib>

#ifdef WIN32
#include <Windows.h>

void assert_error(const char *msg, const char *expr, const char *file, unsigned int line, const char *function)
{
    char error[200];
    sprintf_s(error, "%s\n%s:%d (in %s). %s is false.\n", msg, file, line, function, expr);

    MessageBox(NULL, error, "sputnik", MB_ICONERROR);
    exit(-1);
}

#else

void assert_error(const char *msg, const char *expr, const char *file, unsigned int line, const char *function)
{
    fprintf(stderr, msg);
    fprintf(stderr, "\n\t%s:%d (in %s). %s is false.\n", file, line, function, expr);
    fprintf(stderr, "\n");
    exit(-1);
}

#endif
