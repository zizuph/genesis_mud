/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;


void create_cave()
{
    add_exit(CAVE_DIR + "t55", "north");
    add_exit(CAVE_DIR + "t53", "south");
}

// We don't want any goblins cloned here
void reset_shire_room() {}
