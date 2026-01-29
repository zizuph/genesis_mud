/* goblin caves */
#include "../local.h"

inherit CAVE_GUARD_ROOM;

void create_cave()
{
    add_exit(MISTY_DIR+"p20", "east");
    add_exit(CAVE_DIR+"t58", "west");
    set_guards(2);
}
