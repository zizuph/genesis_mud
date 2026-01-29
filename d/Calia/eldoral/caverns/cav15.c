#include "defs.h"

inherit CAVBASE;

public void
create_room()
{
    create_cavern(2);
    dir_up = ({"northwest"});
    create_base();
    add_exit(CAVERNS + "cav12", "northwest");
}
