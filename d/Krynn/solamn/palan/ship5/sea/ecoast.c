/*
 * Creator: Shadowlynx
 * Date   : February/98
 * File   : /d/Krynn/solamn/palan/ship5/pcoast.c
 * Updated:
 * By Whom:
 */

/* In the strait between Northern and Southern Ergoth coastlines */
#include <stdproperties.h>
#include "defs.h"
#include "../local.h"
#pragma save_binary

inherit "/std/room";

create_room()
{
    set_short("In the sea between the Northern and Southern" +
      " Ergoth coastlines");
    set_long("You are surrounded by the sea in all directions " +
      " except to the north where you can make out the coastline" +
      " of Northern Ergoth and to the south, where the coastline" +
      " of Southern Ergoth is visible. It is said that these" +
      " waters are patrolled by Ergothian pirates.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_exit(SEA + "sea2", "east", 0,1,1);
    add_exit(SEA + "sea3", "northwest", 0,1,1);
}

