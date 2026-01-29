// town hall - village guard hq
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
object   *npc=allocate(5);
 
public void make_npc(int i, string name)
{
   if (npc[i]) return;
   npc[i] = clone_object(NPC+name);
   npc[i]->equip_me();
   npc[i]->move(TO);
   tell_room(TO,QCNAME(npc[i])+" enters from the east.\n");
}
 
public void reset_room()
{
   make_npc(0,"teacher");
   make_npc(1,"child");
   make_npc(2,"child");
   make_npc(3,"child");
   make_npc(4,"child");
}
 
public void create_khalakhor_room()
{
   set_short("Schoolhouse of Baile Ashlagh");
   set_long(
      "Rows of wooden desks and benches line this small one room "+
      "village school house, all facing front where there is a larger "+
      "desk and chair for the teacher. Other than the desks, it is "+
      "furnished only with a small bookshelf along the east wall. From "+
      "the size of the students' desks, you can tell that only small "+
      "children are normally educated here.\n");
 
   add_item(({"school","office","building","hall","room"}),
      "The school is made like all the other buildings of the "+
      "village, a wood-plank building painted in pastel yellow "+
      "with walls framed and crossed by heavy dark beams.\n");
   add_item(({"desks","benches"}),
      "The small desks and benches are crude in form but functional. "+
      "Their size implies that only the small children of the village "+
      "are educated here.\n");
   add_item(({"desk","chair"}),
      "The desk and chair are made of polished wood, though simple "+
      "in design. The chair is cushioned and looks fairly comfortable.\n");
   add_item(({"shelf","bookshelf","books","documents"}),
      "There is a simple wooden bookshelf sitting along the east "+
      "wall packed with books, probably for small children.\n");
   add_item(({"roof","ceiling","floor"}),
      "The roof of the hall made of high angled rafters covered with "+
      "wood planks, just like the floor.\n");
 
   add_exit("court2","west");
   reset_room();
}
