/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 */
 

#pragma strict_types

#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit "/d/Shire/std/room.c";
inherit TUNNEL_BASE;

void
create_tunnel_room()
{
    set_long("@@tunnel_desc1@@");
    add_my_desc("The tunnel runs east and northeast into dark " +
        "blackness.\n");

    add_exit(TUN_DIR + "ta02", "east");
    add_exit(TUN_DIR + "tb03", "northeast");

    reset_shire_room();
}


void reset_shire_room()
{
    int clone_trolls=(random(2));

    if (clone_trolls == 1)
    {
        make_trolls();
    }
 
}

