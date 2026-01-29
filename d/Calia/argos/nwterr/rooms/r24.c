/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A marble road along a river");
   set_long(
       "You are walking down a marble road which runs along the " +
       "northern bank of a rushing river. The forest begins " +
       "to thin here a bit, as the river seems to widen, roaring " +
       "over boulders in the middle. The road follows the river " +
       "to the west and east.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It runs along the river to the west and east.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n");
    add_item("forest",
        "Stately oaks and maples grow all around along the " +
        "northern side of the road, their canopy shedding a little " +
        "shade in front of you.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r23","west",0);
    add_exit(ROOM_DIR+"r25","east",0);
}
