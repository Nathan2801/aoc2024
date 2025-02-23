#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} rule_t;

/** NOTE: file specific variables. */
const int rules_count       = 1176;
const int update_count      = 194;
const int max_update_values = 23;
const int max_line_length   = 128;

struct {
    /** Array to store our input rules. */
    struct {
        rule_t  values[rules_count];
        int     size;
    } rules;
    /** Two dimensional array to store our update values. */
    struct {
        int values[update_count][max_update_values];
        int size;
    } updates;
    /** A array of update values sizes. */
    int update_values_size[update_count];
} input = {0};

void reorder_update(int *update, int update_size, int output[max_update_values]) {
    /** Itearte each update. */
    for (int i = 0; i < update_size; i++) {
        int numbers_before = 0;
        /** Iterate each rule. */
        for (int j = 0; j < input.rules.size; j++) {
            rule_t rule = input.rules.values[j];
            /** Ignore if rule's {y} is not our number. */
            if (rule.y != update[i]) {
                continue;
            }
            /** Check if update has rule's {x} number. */
            bool has_x = false;
            for (int k = 0; k < update_size; k++) {
                if (update[k] == rule.x) {
                    has_x = true;
                }
            }
            /** Ignore rule if we didn't found {x}. */
            if (!has_x) {
                continue;
            }
            /** If all passes we say that our number should
             *  have one more number before it. */
            numbers_before++;
        }
        /** Use {numbers_before} as new index. */
        output[numbers_before] = update[i];
    }
    return;
}

bool is_update_correctly_ordered(int *update, int update_size) {
    /** Iterate each rule. */
    for (int i = 0; i < input.rules.size; i++) {
        int x_index = -1;
        int y_index = -1;
        rule_t rule = input.rules.values[i];
        /** Iterate each value looking for rule's values. */
        for (int j = 0; j < update_size; j++) {
            if (update[j] == rule.x) {
                x_index = j;
            } else if (update[j] == rule.y) {
                y_index = j;
            }
        }
        /** Ignore rule if one of values are not present. */
        if (x_index == -1 || y_index == -1) {
            continue;
        }
        /** Apply rule. */
        if (x_index > y_index) {
            return false;
        }
    }
    return true;
}

int parse_rule_line(char *line) {
    rule_t rule = {0};
    assert(sscanf(line, "%d|%d", &rule.x, &rule.y) == 2);
    input.rules.values[input.rules.size++] = rule;
}

int parse_update_line(char *line) {
    char *token = strtok(line, ",");
    int *update = input.updates.values[input.updates.size];
    while (token != NULL) {
        int n = atoi(token);
        int *index = &input.update_values_size[input.updates.size];
        assert(*index < max_update_values);
        update[(*index)++] = n;
        token = strtok(NULL, ",");
    }
    input.updates.size++;
}

int parse(FILE *in_file) {
    char line[max_line_length] = {0};
    bool parsing_rules = true;
    while (true) {
        int ret = fscanf(in_file, "%[^\n]", line);
        if (ret == EOF) {
            break;
        }
        if (ret == 0) {
            parsing_rules = false;
        } else {
            if (parsing_rules) {
                parse_rule_line(line);
            } else {
                parse_update_line(line);
            }
        }
        assert(fgetc(in_file) == '\n');
    }
    return 0;
}

int part_one() {
    int result = 0;
    for (int i = 0; i < input.updates.size; i++) {
        int *update = input.updates.values[i];
        int update_size = input.update_values_size[i];
        if (is_update_correctly_ordered(update, update_size)) {
            result += update[(int) update_size/2];
        }
    }
    return result;
}

int part_two() {
    int result = 0;
    for (int i = 0; i < input.updates.size; i++) {
        int *update = input.updates.values[i];
        int update_size = input.update_values_size[i];
        /** Ignore the correct ones. */
        if (is_update_correctly_ordered(update, update_size)) {
            continue;
        }
        int reordered[max_update_values] = {0};
        reorder_update(update, update_size, reordered);
        result += reordered[(int) update_size/2];
    }
    return result;
}

int main() {
    FILE *in_file = fopen("./day5.in", "r");
    assert(in_file != NULL && "failed to open input file");

    parse(in_file);

    int r1 = part_one();
    printf("Part one result: %d\n", r1);

    int r2 = part_two();
    printf("Part two result: %d\n", r2);

    return 0;
}
