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
    add_my_desc("\n");

    add_exit(TUN_DIR + "ta07", "east");
    add_exit(TUN_DIR + "tb05", "northwest");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

