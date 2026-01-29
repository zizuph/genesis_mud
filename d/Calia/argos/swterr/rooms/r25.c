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
      "The road bends to from the west to the southeast here, following "+
      "the path of the river on the north side. A grove of olive trees "+
      "grows behind a crude fence which lines the south side of the "+
      "road, keeping you on the dusty path.\n");
 
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its southern bank.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "The forest on the other side of the river is filled with oaks and " +
      "maples.\n");
   add_item("forest",
       "The trees on the other side of the river grow stately with their "+
       "massive trunks. They look rather ancient.\n");
   add_item(({"grove","trees","olive trees","tree","olive tree"}),
       "A grove of olive trees grows behind a fence on the south side "+
       "of the dusty road, their branches laden with ripe fruit.\n");
   add_item("fence",
       "It is a rather crude but high and sturdy fence which protects "+
       "the olive grove. It would be too difficult to scale it.\n");
   add_item(({"olive","olives"}),
      "They weight down the branches of the trees in the grove.\n");
   add_cmd_item(({"olive","olives","olives on trees","olives from trees"}),
      ({"get","pick"}),"You can not reach them from here.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"r24","west",0);
   add_exit(ROOM_DIR+"r26","southeast",0);
}
