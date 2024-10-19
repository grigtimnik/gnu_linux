
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_SUBSTITUTION_LENGTH 1000
#define MAXGR 10

void handle_regex_error(int errcode, regex_t *regex) {
    char buffer[100];
    regerror(errcode, regex, buffer, sizeof(buffer));
    fprintf(stderr, "Regex error: %s\n", buffer);
}

int substitute(const char *regexp, const char *substitution, const char *string) {
    regex_t regex;
    regmatch_t matches[MAXGR];
    char result[MAX_SUBSTITUTION_LENGTH];
    
    int errcode = regcomp(&regex, regexp, REG_EXTENDED);
    if (errcode != 0) {
        handle_regex_error(errcode, &regex);
        return 1;
    }

    const char *source_ptr = string;
    char *result_ptr = result;
    
    if (regexec(&regex, source_ptr, MAXGR, matches, 0) == 0) {
        size_t prefix_len = matches[0].rm_so;
        strncpy(result_ptr, source_ptr, prefix_len);
        result_ptr += prefix_len;

        const char *sub_ptr = substitution;
        while (*sub_ptr && result_ptr - result < sizeof(result) - 1) {
            if (*sub_ptr == '\\' && *(sub_ptr + 1) >= '0' && *(sub_ptr + 1) <= '9') {
                int pocket_num = *(sub_ptr + 1) - '0';
                sub_ptr += 2;
                if (matches[pocket_num].rm_so == -1) {
                    fprintf(stderr, "Error: Invalid reference \\%d\n", pocket_num);
                    regfree(&regex);
                    return 1;
                }
                size_t match_length = matches[pocket_num].rm_eo - matches[pocket_num].rm_so;
                strncpy(result_ptr, source_ptr + matches[pocket_num].rm_so, match_length);
                result_ptr += match_length;
            } else if (*sub_ptr == '\\' && *(sub_ptr + 1) == '\\') {
                *result_ptr++ = '\\';
                sub_ptr += 2;
            } else {
                *result_ptr++ = *sub_ptr++;
            }
        }

        const char* suffix_start = source_ptr + matches[0].rm_eo;
        size_t suffix_len = strlen(suffix_start);
        strncpy(result_ptr, suffix_start, suffix_len);
        result_ptr += suffix_len;

        *result_ptr = '\0';
    } else {
        strncpy(result, string, MAX_SUBSTITUTION_LENGTH - 1);
        result[MAX_SUBSTITUTION_LENGTH - 1] = '\0';
    }

    printf("%s\n", result);
    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: esub <regexp> <substitution> <string>\n");
        return 1;
    }
    return substitute(argv[1], argv[2], argv[3]);
}
