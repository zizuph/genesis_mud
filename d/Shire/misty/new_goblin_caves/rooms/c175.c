/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c184", "northeast");
	add_exit(ROOMS_DIR + "c176", "west");
	add_exit(ROOMS_DIR + "c182", "northwest");
	add_exit(ROOMS_DIR + "c174", "south");

}
