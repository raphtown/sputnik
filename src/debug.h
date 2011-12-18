#ifndef _DEBUG_H
#define _DEBUG_H

#include <cstdio>

#define SPUTNIK_ASSERT(expr, msg) \
	if (!(expr)) { \
		fprintf(stderr, msg); \
		fprintf(stderr, "\n\t%s:%d (in %s). %s is false.\n", __FILE__, __LINE__, __FUNCTION__, (#expr)); \
		fprintf(stderr, "\n"); \
		exit(-1); \
	}

#endif