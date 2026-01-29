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
    add_my_desc("The tunnel is dark and forboding as it bends " +
        "northeast and west.\n");

    add_exit(TUN_DIR + "tag04", "east");
    add_exit(TUN_DIR + "ta17", "west");
    add_exit(TUN_DIR + "ta19", "northeast");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

