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

string extra_line = "";
#define DROW_DIR    "/d/Faerun/guilds/drow/rooms/"
void
create_tunnel()
{
    add_prop(ROOM_M_NO_TELEPORT,1);

    set_short("A dark tunnel");
    set_long(tun_desc4(extra_line));

    reset_room();

    add_exit(TUN_DIR + "u36", "east");
    add_exit(TUN_DIR + "u34", "northeast");
    add_exit(DROW_DIR + "join", "southwest");

}

public void
init()
{
    ::init();

}
void
reset_room()
{
}
