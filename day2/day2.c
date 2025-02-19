#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

const int lines = 1000;
const int limit = 8;

int in[lines][limit] = {0};

/** This function iterate the report values, take
 *  the current value {a} and the next value {b}, and
 *  make sure they follow the rules in the problem.
 *
 *  For the 2th part, we introduced {index_to_ignore},
 *  which inform us a index that should not be used,
 *  when this index is used in {a} we try to take the
 *  previous index, when in {b} we try the next one,
 *  if they are not available we follow the proper
 *  program logic. */
bool is_safe_report(int report_line, int index_to_ignore) {
    int increasing = -1;
    int *report = in[report_line];
    for (int i = 0; i + 1 < limit; i++) {
        int a = report[i];
        if (i == index_to_ignore) {
            if (i - 1 < 0) {
                continue;
            }
            a = report[i - 1];
        }
        int b = report[i + 1];
        if (i + 1 == index_to_ignore) {
            if (i + 2 >= limit || report[i + 2] == 0) {
                break;
            }
            b = report[i + 2];
        }
        if (b == 0) {
            break;
        }
        int d = abs(a - b);
        if (d < 1 || d > 3) {
            return false;
        }
        if (increasing == -1) {
            increasing = a < b;
        } else if (increasing && a > b) {
            return false;
        } else if (!increasing && a < b) {
            return false;
        }
    }
    return true;
}

int part_one() {
    int result = 0;
    for (int i = 0; i < lines; i++) {
        if (is_safe_report(i, -1)) {
            result++;
        }
    }
    return result;
}

int part_two() {
    int result = 0;
    for (int i = 0; i < lines; i++) {
        if (is_safe_report(i, -1)) {
            result++;
            continue;
        }
        for (int j = 0; j < limit && in[i][j] != 0; j++) {
            if (is_safe_report(i, j)) {
                result++;
                break;
            }
        }
    }
    return result;
}

int main() {
    FILE *in_file = fopen("./day2.in", "r");
    assert(in_file != NULL && "failed to open input file");

    int item_index = 0;
    int line_number = 0;
    while (true) {
        char c = fgetc(in_file);
        if (c == EOF) {
            break;
        }
        if (isdigit(c)) {
            fseek(in_file, -1, SEEK_CUR);
            fscanf(in_file, "%d", &in[line_number][item_index]);
            item_index++;
        } else if (c == '\n') {
            line_number++;
            item_index = 0;
        }
    }

    int r1 = part_one();
    printf("Part one result: %d\n", r1);

    int r2 = part_two();
    printf("Part two result: %d\n", r2);

    fclose(in_file);
    return 0;
}
