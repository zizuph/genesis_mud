/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 1993     Zima             Created
** 9/15/96  Zima             Cleaned up, messages added to mountain exits
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A marble road through the mountains");
   set_long(
       "You are walking along a marble road in a range of mountains. " +
       "The road is surrounded by large boulders and a dense forest, " +
       "while a brisk moutain wind ruffles your hair. The road steepens up " +
       "into the heights of the mountains to the west, and leads east " +
       "into the foothills, beyond which you see a forested valley.\n");
 
    add_item("road",
       "Made of long slabs of white marble, this road seems fairly " +
       "new. It leads into the foothills to the east, and further " +
       "up into the mountains to the west.\n");
    add_item(({"forest","trees"}),
       "A mixture of maples, oaks and evergreens, the forest " +
       "grows densly on either side of the road, keeping you " +
       "on your path.\n");
    add_item("mountains",
       "Looming along the eastern horizon, the mountains seem high but " +
       "passable along the marble road.\n");
    add_item("boulders",
       "Huge mounds of granite, these boulders dot the mountains " +
       "and their foothills, interspersed with the trees of the " +
       "forest.\n");
 
    /* exits */
    add_exit(ROOM_DIR+"r11","up","@@doup");
    add_exit(ROOM_DIR+"r13","east",0);
}
int doup() {
   write("You walk west along the road, climbing up into the mountains.\n");
   return 0;
}
