/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t54", "north");
    add_exit(CAVE_DIR + "t52", "south");
}

// We don't want to clone npcs via the inherited file
void reset_shire_room() {}
