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
    set_long("@@tunnel_desc4@@");
    add_my_desc("\n");
    set_add_bones();

    add_exit(TUN_DIR + "ta01", "west");
    add_exit(TUN_DIR + "ta03", "southeast");

    reset_shire_room();
}


void reset_shire_room()
{
        make_trolls();     
}
