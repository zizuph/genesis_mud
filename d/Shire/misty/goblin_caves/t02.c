/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR + "t03", "east");
    add_exit(CAVE_DIR + "t01", "west");

    set_pull(CAVE_DIR+"t11", "south");
    set_push(CAVE_DIR+"t33", "north");
}
