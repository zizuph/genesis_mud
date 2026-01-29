/*
 * Tunnel beneath the Trollshaws
 * By Finwe, August 2001
 * Grouthaur use to be here, but he's been moved to tcg02
 * -- Finwe, Janurary 2018
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
    set_long("@@tunnel_desc6@@");
    add_my_desc("The tunnel becomes wider here. Many exits lead " +
        "off in various directions. The main ones lead north, " +
        "west, and southeast.\n");

    add_exit(TUN_DIR + "ta24a", "north");
    add_exit(TUN_DIR + "ta15", "west");
    add_exit(TUN_DIR + "ta17", "southeast");
    reset_shire_room();
}


void reset_shire_room()
{
    make_trolls();     
}
