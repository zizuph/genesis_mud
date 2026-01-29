/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void
create_room()
{
   set_short("A marble road through the mountains");
   set_long(break_string(
       "You are walking along a marble road in a range of mountains.  " +
       "The road is surrounded by large boulders and a dense forest, " +
       "while a brisk moutain wind ruffles your hair.  The road steepens up " +
       "into the heights of the mountains to the west, and leads east " +
       "into the foothills, beyond which you see a forested valley.\n",70));
 
    add_item("road", break_string(
       "Made of long slabs of white marble, this road seems fairly " +
       "new.  It leads into the foothills to the east, and further " +
       "up into the mountains to the west.\n",70));
 
    add_item(({"forest","trees"}), break_string(
        "A mixture of maples, oaks and evergreens, the forest " +
        "grows densly on either side of the road, keeping you " +
        "on your path.\n",70));
 
    add_item("mountains", break_string(
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n",70));
 
    add_item("boulders", break_string(
        "Huge mounds of granite, these boulders dot the mountains " +
        "and their foothills, interspersed with the trees of the " +
        "forest.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"r11","up",0);
    add_exit(ROOM_DIR+"r13","east",0);
}
