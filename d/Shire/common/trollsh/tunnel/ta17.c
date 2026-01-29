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
    set_long("@@tunnel_desc1@@");
    add_my_desc("The dark and dangerous tunnel bends northwest " +
        "and east beneath the Trollshaws.\n");

    add_exit(TUN_DIR + "ta16", "northwest");
    add_exit(TUN_DIR + "ta18", "east");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

