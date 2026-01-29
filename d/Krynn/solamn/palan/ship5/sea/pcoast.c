/*
 * Creator: Shadowlynx
 * Date   : February/98
 * File   : /d/Krynn/solamn/palan/ship5/pcoast.c
 * Updated:
 * By Whom:
 */

/* Near the Palanthas coastline */
#include <stdproperties.h>
#include "defs.h"
#include "../local.h"
#pragma save_binary

inherit "/std/room";

create_room()
{
    set_short("In the sea near the Palanthas coastline");
    set_long("You are surrounded by the sea in all directions " +
      " except to the southeast where you can see the" +
      " coastline of Palanthas.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_exit(SHIP_S + "pier", "southeast", 0,1,1);
    add_exit(SEA + "sea1", "southwest", 0,1,1);
}

