/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;


void create_cave()
{
    add_exit(CAVE_DIR + "t52", "northeast");
    add_exit(CAVE_DIR + "t50", "south");
}

// We don't want any npcs to be cloned here via the inherited room
void reset_shire_room() {}
