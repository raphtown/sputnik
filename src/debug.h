#ifndef _DEBUG_H
#define _DEBUG_H

void assert_error(const char *msg, const char *expr, const char *file, unsigned int line, const char *function);

#define SPUTNIK_ASSERT(expr, msg) \
	do { \
		if (!(expr)) { \
			assert_error((msg), (#expr), __FILE__, __LINE__, __FUNCTION__); \
		} \
	} while (0);

#endif
