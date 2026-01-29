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
        "You continue along the northern bank of the river on a marble " +
        "road leading through the forest.  The rushing sound of the " +
        "river lulls peacefully, but for some reason you feel a bit " +
        "uneasy here.  Some trees have been cleared away to the north, " +
        "while the marble road follows the river to the east and west.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It runs along the river to the west and east.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n",70));
 
    add_item("forest", break_string(
        "Stately oaks and maples grow densely all around along the " +
        "northern side of the road, though some seem to have been " +
        "cleared away.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r18","west",0);
    add_exit(ROOM_DIR+"r20","east",0);
    add_exit(ROOM_DIR+"for4","north",0);
}
