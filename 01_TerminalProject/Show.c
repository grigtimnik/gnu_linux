#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_LINE_LENGTH 1024 

char** load_file(const char *filename, int *num_lines) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file");
        exit(EXIT_FAILURE);
    }

    char **lines = NULL;
    char buffer[MAX_LINE_LENGTH];
    *num_lines = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        lines = realloc(lines, (*num_lines + 1) * sizeof(char *));
        lines[*num_lines] = strdup(buffer);
        (*num_lines)++;
    }

    fclose(fp);
    return lines;
}

void free_lines(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    int num_lines;
    char **lines = load_file(filename, &num_lines);

    initscr(); 
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int height, width;
    getmaxyx(stdscr, height, width);
    int lines_per_page = height - 2;  // filename and newline after it 

    int current_line = 0;
    int ch;

    while (1) {
        werase(stdscr);
        mvprintw(0, 0, "File: %s", filename);

        for (int i = 0; i < lines_per_page && (current_line + i) < num_lines; i++) {
            mvprintw(i + 2, 0, "%.1024s", lines[current_line + i]);  // line print
        }

        refresh();
        ch = getch();

        if (ch == 27) {  // ESC
            break;
        } else if ((ch == ' ' || ch == KEY_DOWN) && (current_line + lines_per_page) < num_lines) {  // Space
            current_line += 1;
        } else if (ch == KEY_UP && current_line > 0) {  // KEY_UP
            current_line -= 1;
        }

    }

    endwin();
    free_lines(lines, num_lines);

    return 0;
}
