/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    add_exit(ROOMS_DIR + "c121", "north");
	add_exit(ROOMS_DIR + "c120", "northwest");
	add_exit(ROOMS_DIR + "c123", "south");
	
	

}
