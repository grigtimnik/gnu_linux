
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int move_file(const char *infile, const char *outfile) {
    if (!strcmp(infile, outfile)){
        return 0;
    }

    FILE *source = fopen(infile, "r");
    if (!source) {
        fprintf(stderr, "Error opening input file %s\n", infile);
        return 20;
    }

    FILE *destination = fopen(outfile, "w");
    if (!destination) {
        fclose(source);
        fprintf(stderr, "Error opening output file %s\n", outfile);
        return 21;
    }

    char buffer[BUF_SIZE];
    size_t size;
    while ((size = fread(buffer, 1, BUF_SIZE, source)) > 0) {
        if (fwrite(buffer, 1, size, destination) != size) {
            fclose(source);
            fclose(destination);
            remove(outfile);
            fprintf(stderr, "Error writing to output file\n");
            return 22;
        }
    }

    fclose(source);

    if (fclose(destination) != 0) {
        fprintf(stderr, "Error closing output file\n");
        return 23;
    }

    if (remove(infile) != 0) {
        fprintf(stderr, "Error deleting input file\n");
        return 24;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: move infile outfile\n");
        exit(1);
    }

    return move_file(argv[1], argv[2]);
}
