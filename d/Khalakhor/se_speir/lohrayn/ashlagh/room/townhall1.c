// town hall - mayor's office
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
object   mayor;
 
public void reset_room()
{
   if (mayor) return;
   mayor = clone_object(NPC+"mayor");
   mayor->equip_me();
   mayor->move(TO);
   tell_room(TO,QCNAME(mayor)+" enters from the east.\n");
}
 
public void create_khalakhor_room()
{
   set_short("village hall");
   set_long(
      "This is the office of the Maighstir, or mayor, of the village. "+
      "A large desk with a comfortable chair sits on a carpet in the "+
      "center of the office, which is decorated only with a banner "+
      "hanging on the west wall and a bookshelf on the south.\n");
 
   add_item(({"office","building","hall","room"}),
      "The office is made like all the other buildings of the "+
      "village, a wood-plank building painted in pastel yellow "+
      "with walls framed and crossed by heavy dark beams.\n");
   add_item(({"desk","chair"}),
      "The desk and chair are made of polished wood, though simple "+
      "in design. The chair is cushioned and looks fairly comfortable.\n");
   add_item("carpet",
      "It is a wool carpet made of purple-dyed threads interwoven with "+
      "intricate circles and scrolls in a typical celtic design.\n");
   add_item("banner",
      "The banner hanging on the west wall is purple with nine "+
      "sailing ships.\n");
   add_item(({"shelf","bookshelf","books","documents"}),
      "There is a simple wooden bookshelf sitting along the south "+
      "wall, packed with books and documents.\n");
 
   add_item(({"roof","ceiling","floor"}),
      "The roof of the hall made of high angled rafters covered with "+
      "wood planks, just like the floor.\n");
 
   add_exit("townhall","east");
   reset_room();
}
