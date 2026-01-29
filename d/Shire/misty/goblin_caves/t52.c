/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t53", "north");
    add_exit(CAVE_DIR + "t51", "southwest");
}

// Don't clone any npcs here via the inherited room
void reset_shire_room() {}
