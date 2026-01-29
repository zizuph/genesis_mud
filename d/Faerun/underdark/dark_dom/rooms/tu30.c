/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 * Updated desc to include 
 * "southwest" instead of "west"
 * to match the exits of the room. 
 *--Clyptas, July 2018
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

string extraline = "The tunnel takes a sharp turn and heads southwest and " +
    "southeast";

void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc1(extraline));

    reset_room();

    add_exit(TUN_DIR + "tu23", "north");
    add_exit(TUN_DIR + "tu37", "southeast");
    add_exit(TUN_DIR + "tu36", "southwest");

}

public void
init()
{
    ::init();

}
void
reset_room()
{
    set_searched(0);
} 
