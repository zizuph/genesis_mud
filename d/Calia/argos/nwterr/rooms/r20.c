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
       "northern bank of a rushing river, which bends to the " +
       "southeast here.  A small path leads north into the forest, " +
       "while the road follows the river to the west and southeast.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It runs along the river to the west and southeast.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n",70));
 
    add_item("forest", break_string(
        "Stately oaks and maples grow densely all around along the " +
        "northern side of the road.  A small path cuts through to " +
        "the north.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r19","west",0);
    add_exit(ROOM_DIR+"r21","southeast",0);
    add_exit(ROOM_DIR+"past1","north",0);
}
