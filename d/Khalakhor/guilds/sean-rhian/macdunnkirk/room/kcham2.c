/* Kirk of Port City - Living quarters of the manachs
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 7/28/97     Zima        Created
**
*/
/* inherits/includes */
inherit  "/d/Khalakhor/std/room";
#define  NUM 2
#define  INC_KHALSYS_DEFS
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
 
object *monk=allocate(NUM);
 
 
void make_monk(int i, string fname)
{
   if (monk[i]) return;
   monk[i]=clone_object(SR_NPC+fname);
   monk[i]->equip_me();
   monk[i]->move(TO);
   tell_room(TO,QCTNAME(monk[i])+" enters the chamber.\n");
}
 
void reset_room()
{
   make_monk(0,"tinne");      // sick novice
   make_monk(1,"balantrum");  // nurse manach, quest npc
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Living quarters of the abbey");
   set_long(
      "   Rows of neatly placed beds line the walls of this chamber, which "+
      "serves as the sleeping room for the manachs. A tall wardrobe "+
      "stands along the south wall on the right of the entrance, while "+
      "a large chest sits on its left. A long table with a few chairs "+
      "is placed in the middle of the chamber on top of a thick carpet. "+
      "Dim light filters in through windows on the north and west walls.\n");
   INSIDE;
 
   add_item(({"table","chairs","chair"}),
      "A long wooden table sits in the center of the chamber, surrounded "+
      "by a group of chairs. Inornate but clean, its presence is "+
      "probably more utilitarian than decorative.\n");
   add_item(({"rows","beds","bed"}),
      "Rows of beds frame the rectangular chamber on the north, east and "+
      "west sides. Each bed is made of wood with a feather mattress, "+
      "neatly covered with blue blankets.\n");
   add_item("wardrobe",
      "It is a tall, free-standing closet sitting to the right of the "+
      "entrance. It looks to be very old, richly ornamented, and "+
      "highly polished. Its doors are covered with carved branches of "+
      "oak, and are locked with a heavy latch.\n");
   add_item("chest",
      "It is a large chest sitting to the left of the entrance. Made "+
      "to match the wardrobe, its polished surface shines even in "+
      "dim light. Its top is securely closed and locked.\n");
   add_cmd_item(({"wardrobe","chest"}),"open","It is locked.\n");
   add_cmd_item(({"wardrobe","chest"}),"unlock","You do not have the key.\n");
   add_item("carpet",
      "It is a large violet carpet woven of wool, intricately patterned "+
      "and tasseled around the edges. It covers the center of the stone "+
      "floor.\n");
   add_item(({"window","windows"}),
      "The windows are made of opaque panes of cream colored glass "+
      "arranged in a lattice of diamond shapes, like those found "+
      "throughout the abbey.\n");
   add_item("entrance",
      "It leads out of the chamber to the south, flanked by a tall "+
      "wardrobe on one side and a large chest on the other.\n");
 
   add_exit("kcham1","south");
   reset_room();
}
