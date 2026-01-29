/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c138", "southwest");
	add_exit(ROOMS_DIR + "c141", "south");


}
