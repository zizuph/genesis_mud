/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 */
 

#pragma strict_types

inherit "/d/Shire/std/room.c";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;

void
create_tunnel_room()
{
    set_long("@@tunnel_desc3@@");
    add_my_desc("Continuous drops of water fall from the ceiling, " +
        "collecting in pools on the ground. A strong breeze blows " +
        "from the east.\n");
    set_add_water_pools();

    add_exit(TUN_DIR + "tb08", "north");
    add_exit(TUN_DIR + "ta22", "south");
    add_exit(TUN_DIR + "ta23", "east");
    reset_shire_room();

}


void reset_shire_room()
{
        make_trolls();     
}

