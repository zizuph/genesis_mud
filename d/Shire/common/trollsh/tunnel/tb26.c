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
    add_my_desc("The tunnel is straight and runs north and south.\n");

    add_exit(TUN_DIR + "tc03", "north");
    add_exit(TUN_DIR + "tb17", "south");
    add_exit(TUN_DIR + "tbg05", "east");
    reset_shire_room();
}

void reset_shire_room()
{
    clone_trolls = random(2);

    if (clone_trolls == 1) // if 1 make trolls, else no trolls
    {
        make_trolls();     
    }

}

