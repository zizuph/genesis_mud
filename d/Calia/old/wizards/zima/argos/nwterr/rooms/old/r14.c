/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A marble road in a forested valley");
   set_long(
     "You are walking along a marble road through a beautifully forested "+
     "valley. The sun shines brightly through the canopy of the dense "+
     "trees of the forest, and you hear birds singing all around. The road "+
     "climbs up into the foothills of some mountains to the west, and "+
     "continues further east into the valley. A small path leads into the "+
     "deep forest to the north.\n");
 
   add_item("path",
      "It is a small path leading north into the woods.\n");
   add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads up into the foothills to the west, and further " +
       "into the valley to the east.\n");
   add_item("mountains",
       "Looming along the western horizon, the mountains seem high but " +
       "passable along the marble road.\n");
   add_item("forest",
       "A mixture of maples, oaks and evergreens, the forest grows "+
       "densly on either side of the road. A small path leads "+
       "into it to the north.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"sfor1","north",0);
   add_exit(ROOM_DIR+"r13","up",0);
   add_exit(ROOM_DIR+"r15","east",0);
}
