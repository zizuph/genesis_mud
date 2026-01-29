/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c190", "west");
	add_exit(ROOMS_DIR + "c191", "north");
	add_exit(ROOMS_DIR + "c158", "south");

}
