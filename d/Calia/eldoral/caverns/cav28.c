#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_tunnel(3);
    dir_up = ({"west"});
    create_base();
    add_exit(CAVERNS + "cav27", "west");
}
