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
int clone_trolls = random(2);

void
create_tunnel_room()
{
    set_long("@@tunnel_desc3@@");
    add_my_desc("Accumulated pools of water are scattered about. " +
        "The tunnel runs north and southwest.\n");
    set_add_water_pools();

    add_exit(TUN_DIR + "tb24", "north");
    add_exit(TUN_DIR + "tbg04", "west");
    add_exit(TUN_DIR + "ta20", "southwest");


    reset_shire_room();
}

void reset_shire_room()
{
    if (clone_trolls == 1) // if 1 make trolls, else no trolls
    {
        make_trolls();     
    }
    clone_trolls = random(2);

}

