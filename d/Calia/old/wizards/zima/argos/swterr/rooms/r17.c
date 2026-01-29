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
       "The torrents of the flowing river lull you into a sense of "+
       "tranquility as you walk down a dirt road along the river's " +
       "southern bank. A thick forest of towering dark trees along " +
       "the southwestern side of the road keeps you on the newly " +
       "cleared path. The road continues to the northwest and " +
       "southeast along the banks of the river.\n",70));

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
    add_exit(ROOM_DIR+"r16","northwest",0);
    add_exit(ROOM_DIR+"r18","southeast",0);
}

