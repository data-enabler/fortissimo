#include "Utils.h"
#include <stdio.h>

bool safeInit(const char* name, bool (*func) (void)) {
	if(!func()) {
		fprintf(stderr, "%s initialization failed!\n", name);
		return false;
	}
	return true;
}