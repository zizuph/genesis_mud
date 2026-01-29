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
    add_my_desc("Branches lead northeast and southeast as well " +
        "as west.\n");

    add_exit(TUN_DIR + "tag02", "east");
    add_exit(TUN_DIR + "ta10", "west");
    add_exit(TUN_DIR + "ta22", "northeast");
    add_exit(TUN_DIR + "ta12", "southeast");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

