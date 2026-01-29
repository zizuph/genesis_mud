/* Home of the manachs in Tabor Sagh
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/9/98      Zima        Created
**
*/
/* inherits/includes */
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include "kirk.h"
object monk=0;
 
void reset_room() {
   if (!monk) {
      monk=clone_object(SR_NPC+"gebann"); //incense tour npc
      monk->equip_me();
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" enters the room.\n");
   }
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("cozy home");
   set_long(
      "   You are standing in one of the cozy stone walled and thatch "+
      "roofed home's of the village. There are four simple beds lined "+
      "along the wall on the north end of the room, next to a large "+
      "cabinet. An eating table and "+
      "chairs sit before a hearth on the south end. A desk and chair "+
      "sit in the middle of the room, facing the entrance, behind "+
      "which hangs a banner on the east wall next to a bookshelf.\n");
 
   add_item(({"bed","beds"}),
      "Four simple beds, neatly made, line the north wall of the home.\n");
   add_item("cabinet",
      "It is a large wooden cabinet, closed and locked. It probably holds "+
      "the clothing of those who dwell here.\n");
   add_item(({"table","chairs"}),
      "A simple wooden table surrounded by four chairs sits in front of "+
      "the hearth on the south wall. It is neatly cleared away.\n");
   add_item(({"hearth","pots","utensils"}),
      "It is a small stone fire-place with a warm fire burning inside. "+
      "Pots and other cooking utensils hang neatly next to it.\n");
   add_item(({"desk","chair"}),
      "The desk and its chair seem to be the most valuable of the "+
      "home's furnishings, sitting in the center of the home as if in an "+
      "office area.\n");
   add_item("bookshelf",
      "There is an old wooden bookshelf behind the desk along the east "+
      "wall, its shelves lined with books and scrolls.\n");
   add_item("banner",
      "The banner is green and has three interlocked circles on it.\n");
   add_item(({"wall","walls"}),"They are simple stone walls.\n");
   add_item("roof","It is a simple thatched roof.\n");
 
   add_exit("road_1_4","west");
   reset_room();
}
