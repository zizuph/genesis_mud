/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "A light breeze carries a distant pecking sound as you walk " +
       "along the path through the forest. You think it must be a " +
       "woodpecker, but the pitch is a little high for such. The " +
       "path seems a little more used here as it widens toward the "+
       "east.\n");
 
    add_item("path",
        "A narrow dirt path winding through the woods, it widens "  +
        "towards the east.\n");
    add_item(({"canopy","leaves"}),
        "The dense canopy of leaves provides a peaceful shade " +
        "as you walk along the winding path.\n");
    add_item("forest",
        "A mixture of maples, oaks and evergreens, the forest " +
        "surrounds you with its beautiful hardwoods. Wildflowers " +
        "sprout sporadically, searching for patches of sunlight " +
        "filtering through the canopy of leaves.\n");
    add_item(({"flowers","wildflowers"}),
        "Small white flowers on long leafy stems, they grow sporadically " +
        "on the shady floor of the forest.\n");
    add_item("leaves",
        "Some have fallen from the trees onto the path, and crunch under " +
        "your feet as you walk along.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r2a","west",0);
    add_exit(ROOM_DIR+"r3","east",0);
}
