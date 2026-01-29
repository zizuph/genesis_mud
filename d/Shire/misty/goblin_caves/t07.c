/* goblin caves */
#include "../local.h"

inherit CAVE_GUARD_ROOM;

void create_cave()
{
    add_exit(CAVE_DIR + "t20", "east");
    add_exit(CAVE_DIR + "t30", "west");
    add_exit(CAVE_DIR + "t40", "northeast");
    add_exit(CAVE_DIR + "t06", "southwest");
    add_exit(CAVE_DIR + "t08", "southeast");
    set_guards(7);
}
