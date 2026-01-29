/*
 * Creator: Shadowlynx
 * Date   : February/98
 * File   : /d/Krynn/solamn/palan/ship5/pcoast.c
 * Updated:
 * By Whom:
 */

 /* Near the Sancrist coastline */
#include <stdproperties.h>
#include "defs.h"
#include "../local.h"
#pragma save_binary

inherit "/std/room";

create_room()
{
set_short("In the sea near the Sancrist coastline");
set_long("You are surrounded by the sea in all directions " +
" except to the southeast where you can see the coastline" +
" of the port city Xenos and the vast mountain range" +
" beyond where Mount Nevermind, home of the gnomes, is" +
" located.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

add_exit(SEA + "sea4", "northwest", 0,1,1);
add_exit(SHIP_A + "pier", "southeast", 0,1,1);
}

