/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c132", "northwest");
	add_exit(ROOMS_DIR + "c135", "northeast");
	add_exit(ROOMS_DIR + "c136", "southeast");
	add_exit(ROOMS_DIR + "c130", "south");

}
