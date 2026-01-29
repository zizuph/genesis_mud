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
       "You are walking along a marble road which turns to the "  +
       "southeast here to follow a wide, rushing river on its "   +
       "northern side.  The trees of the forest have been cleared "   +
       "somewhat to the east, but the river is too deep to try and " +
       "cross it.  The road follows the river to the southeast, and " +
       "leads towards the foothills of some mountains to the west.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It leads up into the foothills to the west, and further " +
       "into the valley to the southeast.\n",70));
 
    add_item("mountains", break_string(
       "Looming along the western horizon, the mountains seem high but " +
       "passable along the marble road.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n",70));
 
    add_item("forest", break_string(
        "Stately oaks and maples grow densely all around, but " +
        "some have been cleared to the east.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r14","west",0);
    add_exit(ROOM_DIR+"r16","southeast",0);
    add_exit(ROOM_DIR+"for1","east",0);
}
