/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t57", "east");
    add_exit(CAVE_DIR + "t49", "west");
}

// WE don't want any npcs to be cloned here by the inherited room.
void reset_shire_room() {}
