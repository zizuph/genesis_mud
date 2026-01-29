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
    add_my_desc("The tunnel widens into a large hall. Many exits " +
        "lead off deep into the caves. There are two that that " +
        "go east and west.\n");


    add_exit(TUN_DIR + "tbg03", "north");
    add_exit(TUN_DIR + "tag03", "south");
    add_exit(TUN_DIR + "ta26",  "east");
    add_exit(TUN_DIR + "ta24",  "west");
    add_exit(TUN_DIR + "tb11",  "northwest");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}

