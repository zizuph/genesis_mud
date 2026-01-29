/*
 * Orc Racial Guild tunnel
 * This is a normal dark room
 * By Finwe, October 2000
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
    add_prop(ROOM_I_LIGHT, -1); /* dark room */

    set_long("@@tunnel_desc1@@");
    add_my_desc("The tunnel runs northwest and north " +
        "into the mountain.\n");

    add_exit(ORCR_ROOM + "psg02", "northwest");
    add_exit(ORCR_ROOM + "psg04", "north");
}
