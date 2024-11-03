
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rhash.h>
#include <ctype.h>

#ifdef HAVE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

void print_hash(unsigned char *digest, size_t digest_size, int is_hex) {
    char output[130];
    if (is_hex) {
        rhash_print_bytes(output, digest, digest_size, RHPR_HEX);
    } else {
        rhash_print_bytes(output, digest, digest_size, RHPR_BASE64);
    }
    printf("%s\n", output);
}

void hash_data(const char *data, int hash_id, int is_hex) {
    unsigned char digest[64];
    size_t digest_size = rhash_get_digest_size(hash_id);

    rhash_library_init();
    rhash_msg(hash_id, data, strlen(data), digest);

    print_hash(digest, digest_size, is_hex);
}

void hash_file(const char *file_path, int hash_id, int is_hex) {
    unsigned char digest[64];
    size_t digest_size = rhash_get_digest_size(hash_id);

    rhash_library_init();
    if (rhash_file(hash_id, file_path, digest) < 0) {
        fprintf(stderr, "Ошибка чтения файла %s\n", file_path);
        return;
    }

    print_hash(digest, digest_size, is_hex);
}

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
#ifdef HAVE_READLINE
        line = readline("Enter command: ");
        if (!line) break;
        if (*line) add_history(line);
#else
        if (getline(&line, &len, stdin) == -1) break;
        line[strcspn(line, "\n")] = 0;
#endif

        char *hash_name = strtok(line, " ");
        char *path_or_string = strtok(NULL, " ");

        if (!hash_name || !path_or_string) {
            fprintf(stderr, "Неправильная команда.\n");
            continue;
        }

        int is_file = path_or_string[0] != '"';
        int is_hex = isupper(hash_name[0]);
        int hash_id;

        if (strcasecmp(hash_name, "md5") == 0) {
            hash_id = RHASH_MD5;
        } else if (strcasecmp(hash_name, "sha1") == 0) {
            hash_id = RHASH_SHA1;
        } else if (strcasecmp(hash_name, "tth") == 0) {
            hash_id = RHASH_TTH;
        } else {
            fprintf(stderr, "Неопознанная команда: %s\n", hash_name);
            continue;
        }

        if (is_file) {
            hash_file(path_or_string, hash_id, is_hex);
        } else {
            char *data = path_or_string + 1;  // Remove "
            hash_data(data, hash_id, is_hex);
        }
#ifdef HAVE_READLINE
        free(line);
#endif
    }

#ifndef HAVE_READLINE
    free(line);
#endif

    return 0;
}
