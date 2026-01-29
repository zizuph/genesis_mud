/* ARGOS - SWTERR - Dirt road along south bank of river
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
   set_short("A dirt road along a river");
   set_long(
      "A wind dances through the branches of the towering dark pines of "+
      "the black forest to the west, seeming to shake in rage as you "+
      "walk down this dirt road. The walls of the temple across the "+
      "river to the east seem to defy them with their white lustre.\n");
   add_item(({"forest","pines","trees"}),
      "A dark forest of towering pines grows thickly to the west, the long "+
      "needles of the trees looking sharp enough to draw blood.\n");
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its western bank.\n");
   add_item(({"city","Argos","argos"}),
      "The city lies on the eastern side of the river, where you see an "+
      "enormous temple.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "It provides a great amount of protection for the city of Argos "+
      "which is built on its eastern side.\n");
   add_item(({"walls","temple"}),
       "A large temple made of brilliant white marble sits across the "+
       "river to the east, its high walls serving as a fortress to any "+
       "which might successfully cross the river, which would be doubtful.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"r31","north",0);
   add_exit(ROOM_DIR+"r33","south",0);
}
