/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

string extraline = "The tunnel runs north and south.";

void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc3(extraline));

    reset_room();

    add_exit(TUN_DIR + "tu58", "north");
    add_exit(TUN_DIR + "tu63", "south");
}

public void
init()
{
    ::init();

}
void
reset_room()
{
    make_goblins();
    set_searched(0);
}
