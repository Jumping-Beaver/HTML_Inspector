// How to look up an entity quickly?
//
// Looping through the whole entities table is the slowest option. We would need to do binary search or
// build a hash table. A hash table without collisions realistically has filling factor of only 10%. This
// is too memory-inefficient. Even a hash table with at most 3 collisions would have a filling
// factor of only 50%.
//
// Encoding all entities in a single string is most memory-efficient and the lookup is faster than
// in the entities table.
//
// The speed can be improved a lot by indexing by the first character of the entity.
//
// Size of entities struct: 157 kB
// Size of single entities string: 25 kB
// Size of entities array indexed by first character: 27 kB

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "entities.h"

int main()
{
    fputs("const char *entities[256] = {\n", stdout);
    for (int c = 0; c <= 255; ++c) {
        bool print_entries = false;
        for (int i = 0; i < sizeof entities / sizeof *entities; ++i) {
            if (entities[i].entity[0] == c) {
                print_entries = true;
                break;
            }
        }
        if (!print_entries) {
            continue;
        }
        printf("    ['%c'] =\n    \"", c);
        int num_printed = 0;
        for (int i = 0; i < sizeof entities / sizeof *entities; ++i) {
            if (entities[i].entity[0] != c) {
                continue;
            }
            if (num_printed > 90) {
                printf("\"\n    \"");
                num_printed = 0;
            }
            printf("&%s", entities[i].entity);
            if (entities[i].decoding == "\"") {
                fputs("\\\"", stdout);
            }
            else {
                fputs(entities[i].decoding, stdout);
            }
            num_printed += strlen(entities[i].entity) + strlen(entities[i].decoding);
        }
        fputs("\",\n", stdout);
    }
    fputs("};\n", stdout);
}
