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
        "You follow the northern bank of a rushing river along a marble " +
        "road which leads through the forest.  The river's torrents are " +
        "too deep to cross to the south, but the forest seems a little " +
        "less thick to the east.  You can hear the forboding caw of some " +
        "large bird from across the river.  The marble road continues " +
        "northwest and southeast along the river's edge.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It runs along the river to the northwest and southeast.\n",70));
 
    add_item("river", break_string(
       "The river is very wide, and seems deep with its rushing torrents.  " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.  You hear the course call of some bird from there.\n",70));
 
    add_item("forest", break_string(
        "Stately oaks and maples grow densely all around, but " +
        "some have been cleared to the east.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r16","northwest",0);
    add_exit(ROOM_DIR+"r18","southeast",0);
    add_exit(ROOM_DIR+"for3","east",0);
}
