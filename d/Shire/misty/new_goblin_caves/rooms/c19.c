/* goblin caves */
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit CAVES_BASE;

void create_cave()
{
    
    add_exit(ROOMS_DIR + "c18", "northwest");
	add_exit(ROOMS_DIR + "c20", "northeast");

}
