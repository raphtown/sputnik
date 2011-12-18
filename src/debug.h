#ifndef _DEBUG_H
#define _DEBUG_H

#include <cstdio>

void display_error(const char *msg, const char *expr, const char *file, unsigned int line, const char *function);

#define SPUTNIK_ASSERT(expr, msg) \
	do { \
		if (!(expr)) { \
			display_error((msg), (#expr), __FILE__, __LINE__, __FUNCTION__); \
			exit(-1); \
		} \
	} while (0);

#endif