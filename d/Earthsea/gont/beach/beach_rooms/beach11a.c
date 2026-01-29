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

    add_my_desc("\n");
    add_exit("beach11", "west");
    add_exit("beach12", "northeast");
}
