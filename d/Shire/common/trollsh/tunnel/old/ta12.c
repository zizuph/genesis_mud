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
    set_long("@@tunnel_desc5@@");
    add_my_desc("Constant dripping of water has formed pools on " +
       "the ground. The walls are coated with slime from the " +
       "water that runs down the walls.\n");
    set_add_slimy_walls();


    add_exit(TUN_DIR + "ta11", "northwest");
    add_exit(TUN_DIR + "ta13", "east");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

