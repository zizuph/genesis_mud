/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A marble road along a river");
   set_long(break_string(
       "You are walking down a marble road which runs along the " +
       "northern bank of a rushing river, bending to the " +
       "northeast here.  The forest grows densely on the northern " +
       "side of the road, though a few trees seemed to have been " +
       "cleared away.  You hear the hoot of an owl from the "   +
       "canopy of the trees..you wonder if it is watching you.  The " +
       "road follows the river to the west and northeast.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It runs along the river to the west and northeast.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n",70));
 
    add_item("forest", break_string(
        "Stately oaks and maples grow densely all around along the " +
        "northern side of the road, though a few seem to have been " +
        "cleared away.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r21","west",0);
    add_exit(ROOM_DIR+"r23","northeast",0);
    add_exit(ROOM_DIR+"for6","north",0);
}
