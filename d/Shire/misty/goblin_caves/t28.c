/* goblin caves */
#include "../local.h"

inherit CAVE_BASE;

void create_cave()
{
    add_exit(CAVE_DIR+"t27", "northeast");

    set_push(CAVE_DIR+"t04", "northwest");
}
