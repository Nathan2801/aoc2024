#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/** Input specific. */
#define ROWS 130
#define COLS 130

struct {
    int guard;
    int visited;
    char cells[ROWS*COLS];
} input = {0};

/** Returns wheter a symbol is the guard. */
bool is_guard(char symbol) {
    return symbol == '^'
        || symbol == '>'
        || symbol == 'v'
        || symbol == '<';
}

/** Sets {x} and {y} from cell. */
int xy_from_cell(int cell, int *x, int *y) {
    *x = cell % COLS;
    *y = cell / COLS;
    return 0;
}

/** Returns cell from {x} and {y}. */
int cell_from_xy(int x, int y) {
    if (x < 0 || x > COLS) return -1;
    if (y < 0 || y > ROWS) return -1;
    return y * COLS + x;
}

/** Change the guard's direction. */
void guard_turn_right() {
    char *guard = &input.cells[input.guard];
    if (*guard == '^') *guard = '>';
    else if (*guard == '>') *guard = 'v';
    else if (*guard == 'v') *guard = '<';
    else if (*guard == '<') *guard = '^';
    else assert(false && "invalid symbol");
}

/** Moves the guard based on the patrol protocol. */
bool guard_move() {
    int cell;
    int x, y;
    char symbol;

    symbol = input.cells[input.guard]; 
    xy_from_cell(input.guard, &x, &y);

    if (symbol == '^') y -= 1;
    if (symbol == '>') x += 1;
    if (symbol == 'v') y += 1;
    if (symbol == '<') x -= 1;

    cell = cell_from_xy(x, y);
    if (cell == -1) {
        input.visited++;
        return false;
    }

    if (input.cells[cell] == '#') {
        guard_turn_right();
        return guard_move();
    }

    if (input.cells[cell] == '.') {
        input.visited++;
    }

    input.cells[input.guard] = 'x';
    input.cells[cell] = symbol;
    input.guard = cell;

    return true;
}

int parse(FILE *in_file) {
    int cell = 0;
    char chr = 0;
    while (true) {
        chr = fgetc(in_file);
        if (chr == EOF) break;
        if (chr == '\n') continue;
        if (is_guard(chr)) {
            input.guard = cell;
        }
        assert(cell < ROWS*COLS);
        input.cells[cell++] = chr;
    }
    return 0;
}

int part_one() {
    while (guard_move());
    return input.visited;
}

int part_two() {
    return 0;
}

int main() {
    FILE *in_file = fopen("./day6.in", "r");
    assert(in_file != NULL && "failed to open input file");

    parse(in_file);

    int r1 = part_one();
    printf("Part one result: %d\n", r1);

    int r2 = part_two();
    printf("Part two result: %d\n", r2);

    return 0;
}
