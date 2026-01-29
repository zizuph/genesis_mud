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
      "You are at the end of a dirt road which leads onto a bridge over "+
      "the river to the east, and continues north along the river's western "+
      "bank. A forest of dark pine trees grows thickly all around, "+
      "their long black needles dancing in the breeze like small "+
      "daggers.\n");
 
   add_item("bridge",
      "It is a study oak bridge, slightly arched in the middle, which "+
      "spans the width of the river. You can walk onto it to the "+
      "east.\n");
   add_item(({"forest","pines","trees"}),
      "A dark forest of towering pines grows thickly to the west, the long "+
      "needles of the trees looking sharp enough to draw blood.\n");
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its western bank.\n");
   add_item(({"city","Argos","argos"}),
      "The city lies on the eastern side of the river, across the bridge.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "It provides a great amount of protection for the city of Argos "+
      "which is built on its eastern side.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"r32","north",0);
   add_exit(ROOM_DIR+"sbridge","east",0);
}
