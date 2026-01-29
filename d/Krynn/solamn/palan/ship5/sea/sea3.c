/*
 * Creator: Shadowlynx
 * Date   : February/98
 * File   : /d/Krynn/solamn/palan/ship5/pcoast.c
 * Updated:
 * By Whom:
 */

/* In the Ergothian Seas */
#include <stdproperties.h>
#include "defs.h"
#include "../local.h"
#pragma save_binary

inherit "/std/room";

create_room()
{
    set_short("In the Ergothian Seas");
    set_long("You are far out in the Ergothian Seas. You are" +
      " surround by water. You see no land anywhere.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    add_exit(SEA + "ecoast", "southeast", 0,1,1);
    add_exit(SEA + "sea4", "northwest", 0,1,1);
}

