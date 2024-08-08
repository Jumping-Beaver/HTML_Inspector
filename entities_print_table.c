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
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "entities.h"

int main()
{
    fputs("static const char *ENTITIES[1 + (unsigned char) -1] = {\n", stdout);
    for (uint_fast16_t c = 0; c <= 255; ++c) {
        bool print_entries = false;
        for (uint_fast16_t i = 0; i < sizeof entities / sizeof *entities; ++i) {
            if (entities[i].entity[0] == c) {
                print_entries = true;
                break;
            }
        }
        if (!print_entries) {
            continue;
        }
        printf("    ['%c'] =\n    \"", c);
        uint_fast8_t line_length = 0;
        for (size_t i = 0; i < sizeof entities / sizeof *entities; ++i) {
            if (entities[i].entity[0] != c) {
                continue;
            }
            if (line_length > 90) {
                printf("\"\n    \"");
                line_length = 0;
            }
            printf("&%s", entities[i].entity);
            if (entities[i].decoding == "\"") {
                fputs("\\\"", stdout);
            }
            else {
                fputs(entities[i].decoding, stdout);
            }
            line_length += strlen(entities[i].entity) + strlen(entities[i].decoding);
        }
        fputs("\",\n", stdout);
    }
    fputs("};\n", stdout);
}
