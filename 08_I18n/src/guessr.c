#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#include "config.h"

enum {
    MIN_VALUE = 0,
    MAX_VALUE = 100,
    RESPONSE_BUFFER_SIZE = 256
};

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[]) {
    char response[RESPONSE_BUFFER_SIZE];

    setlocale(LC_ALL, "");
    bindtextdomain("guessr", LOCALE_PATH);
    textdomain("guessr");

    printf(_("Think of a number between %d and %d\n"), MIN_VALUE, MAX_VALUE);

    printf(_("Please respond to the following queries with '%s' or '%s'\n"), _("yes"), _("no"));

    int lower_bound = MIN_VALUE, upper_bound = MAX_VALUE, middle;
    while (lower_bound < upper_bound) {
        middle = (lower_bound + upper_bound) / 2;
        printf(_("Is your chosen number greater than %d?\n"), middle);
        scanf("%s", response);
        if (strcmp(response, _("yes")) == 0) {
            lower_bound = middle + 1;
        } else if (strcmp(response, _("no")) == 0) {
            upper_bound = middle;
        }
    }
    printf(_("The number you thought of is %d.\n"), lower_bound);

    return 0;
}