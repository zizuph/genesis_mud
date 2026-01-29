// town hall - village guard hq
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
object   *npc=allocate(3);
 
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
   make_npc(0,"captain");
   make_npc(1,"guard");
   make_npc(2,"guard");
}
 
public void create_khalakhor_room()
{
   set_short("office of the Freiceadanan de Baile Ashlagh");
   set_long(
      "This is the office of the Freiceadanan de Baile Ashlagh, who "+
      "are a volunteer force which acts as the village guard. Typical "+
      "of a small military headquarters, or more perhaps of a police "+
      "force, the walls are decorated with a large emblem on the west, "+
      "a map on the south and a banner on the north. A large desk and "+
      "chair sit atop a carpet in the center of the room, while "+
      "two bookshelves stand along the east side of the room, one "+
      "on either side of the door.\n");
 
   add_item(({"coat-of-arms","arms","emblem","seal"}),
      "It is a shield cast in purple displaying nine sailing ships. "+
      "Two claymores are crossed behind the shield, though the whole "+
      "emblem is only decorative. A streamer beneath the shield "+
      "has the words 'The Village of Baile Ashlagh in Lohrayn' "+
      "scripted upon it, while another across the top reads "+
      "'Freiceadanan'.\n");
   add_item(({"headquarters","office","building","hall","room"}),
      "The office is made like all the other buildings of the "+
      "village, a wood-plank building painted in pastel yellow "+
      "with walls framed and crossed by heavy dark beams. It is "+
      "decorated in typical military style.\n");
   add_item(({"desk","chair"}),
      "The desk and chair are made of polished wood, though simple "+
      "in design. The chair is cushioned and looks fairly comfortable.\n");
   add_item("carpet",
      "It is a wool carpet made of purple-dyed threads interwoven with "+
      "intricate circles and scrolls in a typical celtic design.\n");
   add_item("banner",
      "The banner hanging on the north wall is purple with nine "+
      "sailing ships. A scroll along the bottom reads 'The "+
      "Freiceadanan de Baile Ashlagh'.\n");
   add_item(({"shelfs","bookshelves","books","documents"}),
      "There are two simple wooden bookshelves sitting along the east "+
      "wall, one on either side of the entrance, packed with books "+
      "and documents.\n");
   add_item(({"entrance","doorway","door"}),
      "It is to the east, flanked by two bookshelves.\n");
   add_item(({"roof","ceiling","floor"}),
      "The roof of the hall made of high angled rafters covered with "+
      "wood planks, just like the floor.\n");
   add_item("map","@@read_map");
 
   add_exit("court2","east");
   reset_room();
}
 
string read_map()
{
   return (read_file(DOC+"pubmap.txt"));
}
