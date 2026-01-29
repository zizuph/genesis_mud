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
      "The great river which flows through this valley splits here, "+
      "flowing from the west with one branch running north and the other "+
      "to the south. Far across the split to the northeast you see a great "+
      "arch which spans the northern branch of the river, leading into "+
      "the city of Argos. The dusty road runs northwest along the southern "+
      "bank of the river, and bends to the south between the western bank "+
      "of the southern branch and a fence which protects a grove of olive "+
      "trees.\n");
   add_item("road",
      "A simple dirt road, newly cleared through the forest, which " +
      "follows a river along its southern bank.\n");
   add_item("arch",
      "It is a large marble monument which serves as an entrance to the "+
      "city of Argos. Unfortunately it is on the other side of the "+
      "main stream of the river and you can't reach it from here.\n");
   add_item(({"city","Argos","argos"}),
      "The city lies on the eastern side of the split river, though "+
      "you can't see much of it from here.\n");
   add_item("river",
      "The river is very wide, and seems deep with its rushing torrents. " +
      "The forest on the other side of the river is filled with oaks and " +
      "maples. The river splits just to the northeast of there and runs "+
      "to the north and south, flowing from the west.\n");
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
   add_exit(ROOM_DIR+"r26","northwest",0);
   add_exit(ROOM_DIR+"r28","south",0);
}
