/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;


void create_cave()
{
    add_exit(CAVE_DIR + "gol", "north");
    add_exit(CAVE_DIR + "t54", "south");
}

// No cloning of goblins here
void reset_shire_room() {}
