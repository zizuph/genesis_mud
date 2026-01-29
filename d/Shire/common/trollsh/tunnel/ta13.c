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
    add_my_desc("The walls of the tunnels look slimy from the " +
        "constant drips of water that run down them.\n");
    set_add_slimy_walls();
  
    add_exit(TUN_DIR + "ta14", "northeast");
    add_exit(TUN_DIR + "ta12", "west");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

