#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

const int multiplications_limit = 1024;

struct {
    /** How many multiplication operations we found. */
    int length;
    /** Numbers for each multiplication operation. */
    int numbers[multiplications_limit][2];
    /** Tells whether operation is enabled. */
    bool enabled[multiplications_limit];
} input = {
    .length = 0,
    .numbers = {0},
    .enabled = {false},
};

int parse(FILE *in_file) {
    int op_index = 0;
    bool enabled = true;
    while (!feof(in_file)) {
        int readed = 0;
        int cursor = ftell(in_file);
        /** Check foward for 'mul' keyword. */
        fscanf(in_file, "mul%n", &readed);
        if (readed == 3) {
            /** Parse 'mul' operation. */
            int a, b;
            if (fgetc(in_file) != '(') {
                continue;
            }
            if (fscanf(in_file, "%d", &a) != 1) {
                continue;
            }
            if (fgetc(in_file) != ',') {
                continue;
            }
            if (fscanf(in_file, "%d", &b) != 1) {
                continue;
            }
            if (fgetc(in_file) != ')') {
                continue;
            }
            /** Make sure we safe. We don't need Rust (joking). */
            assert(op_index < multiplications_limit);
            input.numbers[op_index][0] = a;
            input.numbers[op_index][1] = b;
            input.enabled[op_index] = enabled;
            op_index++;
            continue;
        } else {
            fseek(in_file, cursor, SEEK_SET);
        }
        /** Check foward for "don't" keyword.
         *
         *  NOTE: "don't" keyword should be verified
         *  before 'do', otherwise (do)n't would be ok,
         *  and "don't" would never be found. */
        fscanf(in_file, "don't%n", &readed);
        if (readed == 5) {
            enabled = false;
            continue;
        } else {
            fseek(in_file, cursor, SEEK_SET);
        }
        /** Check foward for 'do' keyword. */
        fscanf(in_file, "do%n", &readed);
        if (readed == 2) {
            enabled = true;
            continue;
        } else {
            fseek(in_file, cursor, SEEK_SET);
        }
        /** Consumes a single character. */
        fgetc(in_file);
    }
    input.length = op_index;
    return 0;
}

int part_one() {
    int result = 0;
    for (int i = 0; i < input.length; i++) {
        int a = input.numbers[i][0];
        int b = input.numbers[i][1];
        result += a * b;
    }
    return result;
}

int part_two() {
    int result = 0;
    for (int i = 0; i < input.length; i++) {
        if (input.enabled[i]) {
            int a = input.numbers[i][0];
            int b = input.numbers[i][1];
            result += a * b;
        }
    }
    return result;
}

int main() {
    FILE *in_file = fopen("./day3.in", "r");
    assert(in_file != NULL && "failed to open input file");

    parse(in_file);

    int r1 = part_one();
    printf("Part one result: %d\n", r1);

    int r2 = part_two();
    printf("Part two result: %d\n", r2);

    return 0;
}
