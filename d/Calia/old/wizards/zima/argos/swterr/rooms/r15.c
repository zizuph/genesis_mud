/*
   Dirt road along south bank of river in Argos
   Coder:    Zima
   Purpose:  Main road through southwestern territory.
   History:  01.12.93   Created                         Zima
*/

/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"


object axe=0;
void
reset_room()
{
    if (axe) return;
    axe=clone_object(WEAPON_DIR+"axe");
    axe->move(THIS);
}

/* room definition */
void
create_room()
{
   set_short("End of a dirt road along a river");
   set_long(break_string(
       "You walk to the end of a dirt road which follows the " +
       "southern bank of a rushing river.  A dense forest lines the " +
       "southwestern side of the road, filled with dark trees.  There is a " +
       "stump at the end of the path, where it seems the clearing " +
       "of the trees has stopped.  The forest is so thick all around " +
       "you that the only way out is back southeast.\n",70));

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

   add_item("stump",break_string(
       "It is the remnant of a great mohagany tree which was recently " +
       "cut to clear the road to the northwest. Vicious axe marks " +
       "tell of the violent ending of a piece of nature's beauty.\n",70));

    /* exits */
    add_exit(ROOM_DIR+"r16","southeast",0);
    reset_room();
}

