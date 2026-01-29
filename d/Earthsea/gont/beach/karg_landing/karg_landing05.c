/* Coded by Ckrik, February 1998 
 * A Karg beach landing.
 * 
 */

#pragma strict_types
#pragma no_clone

#include "default.h"
#include <stdproperties.h>

inherit LANDING;

public void
create_landing()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_extra_long("A tall cliff stops you from going further north.");
    add_item(({"cliff", "tall cliff"}),
      "The cliff is too high and too loosely formed to climb.\n");

    add_exit("karg_landing04", "southwest");

    reset_room();
}
