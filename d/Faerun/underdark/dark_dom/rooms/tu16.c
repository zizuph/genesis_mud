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

string extraline = "";

void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc2(extraline));

    reset_room();

    add_exit(TUN_DIR + "tu15", "west");
    add_exit(TUN_DIR + "tu21", "southeast");
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
