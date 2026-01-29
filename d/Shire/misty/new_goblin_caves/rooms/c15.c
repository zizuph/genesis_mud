/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
  
    add_exit(ROOMS_DIR + "c14", "northeast");
	add_exit(ROOMS_DIR + "c21", "south");
	add_exit(ROOMS_DIR + "c33", "southwest");
	add_exit(ROOMS_DIR + "c35", "southeast");
}
