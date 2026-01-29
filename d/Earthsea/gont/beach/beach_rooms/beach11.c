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

private object *crabs = allocate(2);

public void
reset_room()
{
    int i;

    ::reset_room();

    for(i = 0; i < 2; i++)
    {
        if(!crabs[i])
        {
            crabs[i] = clone_object("/d/Earthsea/gont/beach/npc/crab");
            crabs[i]->move(this_object());
        }
    }
}

public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");

    add_my_desc( "\n");
    add_item (({"beach", "sandy beach"}),
      "The beach is warm yet rough. You feel the crunch of " +
      "broken rocks and the scratching of sand under your feet.\n");

    add_exit("beach11a",  "east");
    add_exit("beach10", "southwest");
}
