#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

const int rows = 140;
const int cols = 140;

char input[rows][cols] = {0};

typedef struct {
    int x, y;
} vec2i_t;

/** Define each direction.
 *
 *  NOTE: Perhaps we could reduce the amount of directions
 *  by comparing each found word with it's reversed one. */
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    TOP_LEFT,
    TOP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    SEARCH_DIRECTION_COUNT,
} search_direction_t;

/** Map every direction with it's direction vector. */
const vec2i_t direction_values[SEARCH_DIRECTION_COUNT] = {
    [UP]            = { 0, -1},
    [DOWN]          = { 0, +1},
    [LEFT]          = {-1,  0},
    [RIGHT]         = {+1,  0},
    [TOP_LEFT]      = {-1, -1},
    [TOP_RIGHT]     = {+1, -1},
    [DOWN_LEFT]     = {-1, +1},
    [DOWN_RIGHT]    = {+1, +1},
};

/** Define a iterator that moves it's position by a direction. */
typedef struct {
    int iteration;
    int iteration_limit;

    vec2i_t value;
    vec2i_t initial;

    search_direction_t direction;
} search_iterator_t;

/** Implement the iterator function. */
bool search_iterator_next(search_iterator_t *it) {
    if (it->iteration >= it->iteration_limit) {
        return false;
    }
    it->value.x = it->initial.x + direction_values[it->direction].x * it->iteration;
    it->value.y = it->initial.y + direction_values[it->direction].y * it->iteration;
    it->iteration += 1;
    return true;
}

/** Use the iterator to take each letter to form a word and
 *  compare it with the expected word. */
bool search_word(search_iterator_t *it, const char *expected_word) {
    int index = 0;
    char word[32] = "";
    while (search_iterator_next(it)) {
        if (it->value.y >= 0 && it->value.y < cols &&
            it->value.x >= 0 && it->value.x < rows)
        {
            word[index++] = input[it->value.y][it->value.x];
        } else {
            /** Not necessary but helps with debugging. */
            word[index++] = '_';
        }
    }
    return strcmp(word, expected_word) == 0;
}

int parse(FILE *in_file) {
    char c = 0;
    vec2i_t p = {0};
    while (true) {
        c = fgetc(in_file);
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            p.y++;
            p.x = 0;
            continue;
        }
        input[p.y][p.x] = c;
        p.x++;
    }
    return 0;
}

int part_one() {
    int result = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int dir = UP; dir < SEARCH_DIRECTION_COUNT; dir++) {
                search_iterator_t it = {0};
                it.initial.x = j;
                it.initial.y = i;
                it.direction = dir;
                it.iteration_limit = 4;
                if (search_word(&it, "XMAS")) {
                    result++;
                }
            }
        }
    }
    return result;
}

int part_two() {
    int result = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            search_iterator_t a_it = {0};
            a_it.initial.x = j;
            a_it.initial.y = i;
            a_it.direction = DOWN_RIGHT;
            a_it.iteration_limit = 3;
            bool a_valid = false;
            if (search_word(&a_it, "MAS")) {
                a_valid = true;
            }
            a_it.iteration = 0;
            if (search_word(&a_it, "SAM")) {
                a_valid = true;
            }
            search_iterator_t b_it = {0};
            b_it.initial.x = j + 2;
            b_it.initial.y = i;
            b_it.direction = DOWN_LEFT;
            b_it.iteration_limit = 3;
            bool b_valid = false;
            if (search_word(&b_it, "MAS")) {
                b_valid = true;
            }
            b_it.iteration = 0;
            if (search_word(&b_it, "SAM")) {
                b_valid = true;
            }
            if (a_valid && b_valid) {
                result++;
            }
        }
    }
    return result;
}

int main() {
    FILE *in_file = fopen("./day4.in", "r");
    assert(in_file != NULL && "failed to open input file");

    parse(in_file);

    int r1 = part_one();
    printf("Part one result: %d\n", r1);

    int r2 = part_two();
    printf("Part two result: %d\n", r2);

    return 0;
}
