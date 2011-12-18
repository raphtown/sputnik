#include "debug.h"

#ifdef WIN32
#include <Windows.h>

void display_error(const char *msg, const char *expr, const char *file, unsigned int line, const char *function) {
	char error[200];
	sprintf_s(error, "%s\n%s:%d (in %s). %s is false.\n", msg, file, line, function, expr);

	MessageBox(NULL, error, "sputnik", MB_ICONERROR);
}

#else

void display_error(const char *msg, const char *expr, const char *file, unsigned int line, const char *function) {
	fprintf(stderr, msg);
	fprintf(stderr, "\n\t%s:%d (in %s). %s is false.\n", __FILE__, __LINE__, __FUNCTION__, (#expr));
	fprintf(stderr, "\n");
}

#endif
