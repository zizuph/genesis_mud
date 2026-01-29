#pragma strict_types
 
#include "/d/Gondor/defs.h"
inherit "/d/Gondor/common/mirkwood/forest/mirk-M";

void
create_map_room()
{
    ::create_map_room();
    remove_exit("west");
//    add_exit(ANDUIN_DIR+"oldpath7", "west", 0, 1);
    add_exit("oldpath7", "west", 0, 1);
}
