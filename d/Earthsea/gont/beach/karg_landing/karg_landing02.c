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
    add_exit("karg_landing01", "south");
    add_exit("karg_landing03", "north");

    reset_room();
}
