/*
* Orc Racial Guild tunnel
* This is a darker room
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
    add_prop(ROOM_I_LIGHT, -2); /* dark room */

    set_long("@@tunnel_desc1@@");
    add_my_desc("The tunnel runs west and south" +
        "deeper into the mountain.\n");

    add_exit(ORCR_ROOM + "psg06", "west");
    add_exit(ORCR_ROOM + "psg08", "south");
}
