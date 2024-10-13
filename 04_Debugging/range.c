#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
            printf("С одним параметром N — выводит в столбик последовательность [0, 1, … N-1] \n");
            printf("С двумя — M, N — последовательность [M, M+1, … N-1] \n");
            printf("С тремя — M, N, S — последовательность [M, M+S, M+2S, … N-1] \n");
            return 0;
    }

    int start = 0;
    int end = 0;
    int step = 1;

    switch (argc) {
        case 2:
            end = atoi(argv[1]);
            break;
        case 3:
            start = atoi(argv[1]);
            end = atoi(argv[2]);
            break;
        case 4:
            start = atoi(argv[1]);
            end = atoi(argv[2]);
            step = atoi(argv[3]);
            break;
    }

    for (int i = start; i < end; i += step) {
        printf("%d\n", i);
    }
    
    return 0;
}