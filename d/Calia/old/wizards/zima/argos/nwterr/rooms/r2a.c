/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A path through the forest");
   set_long(break_string(
       "You continue along the winding path amongst the towering " +
       "trees of a dense forest.  A few leaves have fallen from their " +
       "branches along the path, crunching beneath your feet as " +
       "you walk along.  You see a few wildflowers growing about " +
       "the forest, adding a touch of color to the shady floor of " +
       "the woods.  The path continues through " +
       "the woods to the west and " + "east.\n",70));
 
 
    add_item("path", break_string(
        "A narrow dirt path winding through the woods, covered in "  +
        "leaves fallen from the trees.  It leads west and east through " +
        "the forest.\n",70));
 
    add_item(({"canopy","leaves"}), break_string(
        "The dense canopy of leaves provides a peaceful shade " +
        "as you walk along the winding path.\n",70));
 
    add_item("forest", break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "surrounds you with its beautiful hardwoods.  Wildflowers " +
        "sprout sporadically, searching for patches of sunlight " +
        "filtering through the canopy of leaves.\n",70));
 
    add_item(({"flowers","wildflowers"}), break_string(
        "Small white flowers on long leafy stems, they grow sporadically " +
        "on the shady floor of the forest.\n",70));
 
    add_item("leaves", break_string(
        "Some have fallen from the trees onto the path, and crunch under " +
        "your feet as you walk along.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r2","west",0);
    add_exit(ROOM_DIR+"r2b","east",0);
}
