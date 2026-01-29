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
inherit "/lib/unique";


public void
create_beach()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");

    add_my_desc( "\n");
    add_item (({"beach", "sandy beach"}),
      "The beach is warm yet rough. You feel the crunch of " +
      "broken rocks and the scratching of sand under your feet.\n");

    add_exit("beach05", "north");
    add_exit("beach07", "southwest");
    reset_room();
}


void
reset_room() {
    string file = "/d/Earthsea/roke/thwil/monster/mercenary";
    if (!random(2))
        return;
    
    if (!find_object(file) || sizeof(object_clones(find_object(file))) < 1) {
        setuid();
        seteuid(getuid());

        object ob = clone_object(file);
        ob->move_living("", this_object());
    }
}
