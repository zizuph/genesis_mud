/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR+"t33", "southeast");
    set_push(CAVE_DIR+"t60", "south");
}
