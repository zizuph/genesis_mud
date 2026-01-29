#include "defs.h"

inherit CAVBASE;

public int
go_up()
{
    write("The tunnel climbs sharply then turns into a switchback, " +
        "and you emerge on a higher level facing westwards.\n");
    return 0;
}

public void
create_room()
{
    create_tunnel(2);
    add_extras(POOLS);
    dir_up = ({"west"});
    dir_level = ({"southwest"});
    create_base();
    add_exit(CAVERNS + "cav16", "west", "@@go_up");
    add_exit(CAVERNS + "cav19", "southwest", "@@block_exit");
}
