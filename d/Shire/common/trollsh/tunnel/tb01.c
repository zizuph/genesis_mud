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
    set_long("@@tunnel_desc6@@");
    add_my_desc("The tunnel bends northeast and southeast here.\n");


    add_exit(TUN_DIR + "tbg01", "south");
    add_exit(TUN_DIR + "tc01", "northeast");
    add_exit(TUN_DIR + "tb02", "southeast");
    add_exit(TUN_DIR + "money_room", "west");

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

