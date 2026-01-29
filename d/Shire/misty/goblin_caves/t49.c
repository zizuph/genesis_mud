/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t50", "northwest");
    add_exit(CAVE_DIR + "t56", "east");
    add_exit(CAVE_DIR + "t48", "south");
}

// We don't want any npcs cloned here.
void reset_shire_room() {}
