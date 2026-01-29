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
      "You are walking down a dirt road between a torrential river and a "+
      "grove of olive trees. The road follows the river's path to the "+
      "north and southwest. The high walls of a large marble temple rise "+
      "across the river to the east, the sunlight glinting off its "+
      "fortress-like walls.\n");
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
   add_item(({"grove","trees","olive trees","tree","olive tree"}),
       "A grove of olive trees grows behind a fence on the west side "+
       "of the dusty road, their branches laden with ripe fruit.\n");
   add_item("fence",
       "It is a rather crude but high and sturdy fence which protects "+
       "the olive grove. It would be too difficult to scale it.\n");
   add_item(({"walls","temple"}),
       "A large temple made of brilliant white marble sits across the "+
       "river to the east, its high walls serving as a fortress to any "+
       "which might successfully cross the river, which would be doubtful.\n");
   add_item(({"olive","olives"}),
      "They weight down the branches of the trees in the grove.\n");
   add_cmd_item(({"olive","olives","olives on trees","olives from trees"}),
      ({"get","pick"}),"You can not reach them from here.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"r27","north",0);
   add_exit(ROOM_DIR+"r29","southwest",0);
}
