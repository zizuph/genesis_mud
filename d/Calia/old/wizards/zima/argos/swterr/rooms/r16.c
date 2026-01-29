/*
   Dirt road along south bank of river in Argos
   Coder:    Zima
   Purpose:  Main road through southwestern territory.
   History:  11.12.94   Created                         Zima
*/

/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

/* room definition */
void
create_room()
{
   set_short("A dirt road along a river");
   set_long(break_string(
       "You continue down a newly cleared dirt road along the " +
       "southern bank of a rushing river. You notice a small path " +
       "through the surrounding forest of towering dark trees to " +
       "west, while the dusty road follows the river to the " +
       "northwest and southeast.\n",70));

    add_item("path",break_string(
       "It's a small opening through the dense underbrush of the dark " +
       "forest. You wonder if it is only an animal crossing.\n",70));

    add_item("road", break_string(
       "A simple dirt road, newly cleared through the forest, which " +
       "follows a river along its southern bank.\n",70));

    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river is filled with oaks and " +
       "maples.\n",70));

    add_item(({"forest","trees"}), break_string(
        "Dark mohagany trees, many overgrown with vines, grow densely " +
        "around you, their thick canopy making a dark shade on the forest " +
        "floor.\n",70));

    /* exits */
    add_exit(ROOM_DIR+"r15","northwest",0);
    add_exit(ROOM_DIR+"r17","southeast",0);
    add_exit(ROOM_DIR+"krcamp1","west",0);
}

