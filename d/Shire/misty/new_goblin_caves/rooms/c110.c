/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c109", "northeast");
	add_exit(ROOMS_DIR + "c111", "east");
	add_exit(ROOMS_DIR + "c114", "southeast");
	add_exit(ROOMS_DIR + "c113", "south");
}
