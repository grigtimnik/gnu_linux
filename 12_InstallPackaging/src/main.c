#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>
#include "addition.h"

#define _(STRING) gettext(STRING)

#ifndef LOCALEDIR
#define LOCALEDIR "/usr/local/share/locale"
#endif

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    bindtextdomain("addition", LOCALEDIR);
    textdomain("addition");

    if (argc != 3)
    {
        printf(_("Usage: %s num1 num2\n"), argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int result = add(a, b);
    printf(_("The sum of %d and %d is %d\n"), a, b, result);
    return 0;
}
