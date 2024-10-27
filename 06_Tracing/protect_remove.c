#include <dlfcn.h>
#include <string.h>
#include <stdio.h>

int remove(const char *filename) {
    if (strstr(filename, "PROTECT")) {
        fprintf(stderr, "Attempt to remove protected file: %s\n", filename);
        return -1;
    }

    int (*original_remove)(const char *) = dlsym(RTLD_NEXT, "remove");
    return original_remove(filename);
}