/*
 * Beach in Gont
 * By Finwe
 * April 1997
 */

#pragma strict_types 
#pragma no_clone

#include <macros.h>
#include "default.h"
#include <stdproperties.h>

inherit SANDY;

private object human;

public void
reset_room()
{
    ::reset_room();

    if(!human)
    {
        human = clone_object("/d/Earthsea/gont/beach/npc/human");
        human->move(this_object());
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
    add_exit("beach05", "east");
    add_exit("beach03", "southwest");
    reset_room();
}
