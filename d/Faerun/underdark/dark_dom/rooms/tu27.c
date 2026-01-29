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

string extraline = "The tunnel bends northeast and southwest, going around " +
    "stalagmites and stalactites.";

void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc3(extraline));

    reset_room();

    set_add_stalags();

    add_exit(TUN_DIR + "tu22", "northeast");
    add_exit(TUN_DIR + "tu34", "southwest");
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
