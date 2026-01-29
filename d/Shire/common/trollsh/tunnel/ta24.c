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
    add_my_desc("The tunnel widens here as it leads off in " +
        "different directions. A strong breeze blows from the west, " +
        "strong smelling and dank. A faint light shines from there, too.\n");


    add_exit(TS_DIR + "tunnel1", "west");
    add_exit(TUN_DIR + "ta24a", "east");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

