/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c152", "north");
	add_exit(ROOMS_DIR + "c179", "east");
	add_exit(ROOMS_DIR + "c154", "south");


}
