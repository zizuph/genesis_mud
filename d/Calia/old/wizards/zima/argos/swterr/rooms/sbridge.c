/* ARGOS - SWTERR - Bridge from Alpharon Road (Metro) to Dirt Road
**
** History:
** Date      Coder      Action
** --------- ---------- --------------------------------
** 11/10/95  Zima       Created
**
*/
/* inherits/includes */
inherit  "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("On an arched bridge");
   set_long(
      "You are standing at the crest of an arched bridge made of sturdy "+
      "beams of oak. The wide river which the bridge spans flows beneath "+
      "you, filling your ears with its torrential rush. The bridge leads "+
      "into the city to the east, and out onto a dirt road to the west.\n");
 
   add_item("bridge",
      "It is a study oak bridge, slightly arched in the middle, which "+
      "spans the width of the river.\n");
   add_item(({"forest","pines","trees"}),
      "A dark forest of towering pines grows thickly to the west, the long "+
      "needles of the trees looking sharp enough to draw blood.\n");
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows the river along its western bank.\n");
   add_item(({"city","Argos","argos"}),
      "The city lies on the eastern side of the river\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "It provides a great amount of protection for the city of Argos "+
      "which is built on its eastern side.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"r33","west",0);
   add_exit(METRO_DIR+"rooms/aroad1","east",0);
}
