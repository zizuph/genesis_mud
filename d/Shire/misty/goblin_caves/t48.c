/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t49", "north");
    add_exit(CAVE_DIR + "t47", "south");
}

// We don't want any npcs cloned here via the inherited room.
void reset_shire_room() {}
