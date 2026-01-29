/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
	add_exit(ROOMS_DIR + "c43", "northeast");
	add_exit(ROOMS_DIR + "c45", "northwest");
	add_exit(ROOMS_DIR + "c52", "south");
}
