#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int lines = 1000;

int in[2][lines];

int int_increasing(const void *a, const void *b) {
    int an = *((int *) a);
    int bn = *((int *) b);
    return an - bn;
}

int part_one() {
    qsort(&in[0], lines, sizeof(int), int_increasing);
    qsort(&in[1], lines, sizeof(int), int_increasing);

    int result = 0;
    for (int i = 0; i < lines; i++) {
        int a = in[0][i];
        int b = in[1][i];
        int d = abs(a - b);
        result += d;
    }

    return result;
}

int part_two() {
    int result = 0;
    for (int i = 0; i < lines; i++) {
        int a = in[0][i];
        int t = 0;
        for (int j = 0; j < lines; j++) {
            int b = in[1][j];
            if (a == b) {
                t += 1;
            }
        }
        result += a * t;
    }
    return result;
}

int main() {
    FILE *in_file = fopen("./day1.in", "r");
    assert(in_file != NULL && "failed to open input file");

    int i = 0;
    while (fscanf(in_file, "%d %d", &in[0][i], &in[1][i]) != EOF) {
        i++;
    }

    int r1 = part_one();
    printf("Part one result: %d\n", r1);

    int r2 = part_two();
    printf("Part two result: %d\n", r2);

    fclose(in_file);
    return 0;
}
