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
    set_long("@@tunnel_desc2@@");
    add_my_desc("Small streams of water run down the walls, " +
        "creating more grooves in the walls.\n");

    add_exit(TUN_DIR + "ta15", "northeast");
    add_exit(TUN_DIR + "ta13", "southwest");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

