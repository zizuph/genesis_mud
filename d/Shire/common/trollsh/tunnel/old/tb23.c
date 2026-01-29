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
    set_long("@@tunnel_desc5@@");
    add_my_desc("Dripping water echos in the distance, collecting " +
        "in pools on the ground. The tunnel bends southwest and " +
        "runs west.\n");
    set_add_water_pools();

    add_exit(TUN_DIR + "tb22", "west");
    add_exit(TUN_DIR + "tb13", "southwest");
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

