/*
 * Beach in Gont
 * By Finwe
 * April 1997
 */

#pragma strict_types 
#pragma no_clone

#include "default.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANDY;

public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");

    add_my_desc( "\n");
    add_item (({"beach", "sandy beach"}),
      "The beach is warm yet rough. You feel the crunch of " +
      "broken rocks and the scratching of sand under your feet.\n");

    add_exit("beach17", "north");
    add_exit("beach19", "southeast");
}
