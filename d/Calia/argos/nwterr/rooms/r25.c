/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A marble road along a river");
   set_long(
       "You walk along the northern bank of a rushing river on a marble " +
       "road. The forest to the north is a bit thinner here than further " +
       "west, evidence of recent harvesting. Flowering trees are " +
       "interspersed amongst the hardwoods in the forest, adding a " +
       "touch of color to the view. To the southeast, you see that " +
       "the road leads to some large structure, while it follows the " +
       "bend of the river to the west. A small muddy path leads north "+
       "into the forest.\n");
 
    add_item("path",
        "It is a small muddy path which leads north into the forest.\n");
    add_item("structure",
        "A high structure, seemingly made of white marble. You can't make " +
        "out what it is from here.\n");
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It runs along the river to the west and southeast.\n");
    add_item("river",
       "The river is very wide, and seems deep with its rushing torrents. " +
       "The forest on the other side of the river seems dark and " +
       "mysterious.\n");
    add_item("forest",
        "Stately oaks and maples grow all around along the " +
        "northern side of the road, interspersed with flowering " +
        "dogwoods, splashing pink and white in the shade of the " +
        "forest's canopy.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"camp","north",0);
    add_exit(ROOM_DIR+"r24","west",0);
    add_exit(ROOM_DIR+"r26","southeast",0);
}
