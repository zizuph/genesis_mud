/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;


void create_cave()
{
    add_exit(CAVE_DIR + "t42", "east");
    add_exit(CAVE_DIR + "t44", "west");
}
