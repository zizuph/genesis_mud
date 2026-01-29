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
       "northern bank of a rushing river.  The forest grows dense " +
       "along the northern side of the road, but some trees seem "   +
       "to have been cleared to the east.  The river and forest seem " +
       "perfectly safe, but you feel that someone may be watching you." +
       "\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It runs along the river to the northwest and southeast.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n",70));
 
    add_item("forest", break_string(
        "Stately oaks and maples grow densely all around, but " +
        "some have been cleared to the east.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r15","northwest",0);
    add_exit(ROOM_DIR+"r17","southeast",0);
    add_exit(ROOM_DIR+"for2","east",0);
}
