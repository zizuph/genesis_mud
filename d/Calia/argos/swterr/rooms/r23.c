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
 
/* room definition */
void
create_room()
{
   set_short("A dirt road along a river");
   set_long(break_string(
       "You walk along a dirt road which follows the " +
       "southern bank of a rushing river.  A dark forest lines the " +
       "south side of the road, filled with dark trees.  The road " +
       "continues to the east, and bends along the river to the "   +
       "southwest.  You hear the evil caw of some bird from the forest.\n",70));
 
    add_item("road", break_string(
       "A simple dirt road, newly cleared through the forest, which " +
       "follows a river along its southern bank.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river is filled with oaks and " +
       "maples.\n",70));
 
    add_item(({"raven","bird"}), break_string(
        "High in the sky you see a dark bird, what looks like a raven, " +
        "circling ominously overhead. His evil caw " +
        "seems to fill the forest.\n",70));
    add_cmd_item(({"bird","caw","raven"}), "listen",  
        "The forboding call of a dark bird circling above makes you uneasy.\n");
    add_item(({"forest","trees"}), break_string(
        "Dark mohagany trees, many overgrown with vines, grow densely " +
        "around you, their thick canopy making a dark shade on the forest " +
        "floor.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r22","southwest",0);
    add_exit(ROOM_DIR+"r24","east",0);
}
