#include "/d/Gondor/defs.h"
inherit "/d/Gondor/common/mirkwood/forest/mirk-s";

void
create_map_room()
{
    ::create_map_room();
    remove_exit("east");
    add_exit("westbridge2", "east", 0, 1);
}
