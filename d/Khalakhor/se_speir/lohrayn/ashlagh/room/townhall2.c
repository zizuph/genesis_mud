// town hall - records office
inherit "/d/Khalakhor/std/room";
#include "defs.h"
#include <macros.h>
object   mayor;
 
public void reset_room()
{
   if (mayor) return;
   mayor = clone_object(NPC+"secretary");
   mayor->equip_me();
   mayor->move(TO);
   tell_room(TO,QCNAME(mayor)+" enters from the west.\n");
}
 
public void create_khalakhor_room()
{
   set_short("village hall");
   set_long(
      "This office seems to be the hall of records or archives of the "+
      "village, as it is crammed with rows of close-set bookshelves "+
      "filled with large books and other documents, some of which look "+
      "very old and account for the musty smell in the room. Amidst "+
      "the forest of records is a small desk and chair on a carpet.\n");
 
   add_item(({"office","building","hall","room"}),
      "The office is made like all the other buildings of the "+
      "village, a wood-plank building painted in pastel yellow "+
      "with walls framed and crossed by heavy dark beams.\n");
   add_item(({"desk","chair"}),
      "The desk and chair are made simply of wood with no special polish "+
      "or design. The chair is cushioned and looks somewhat comfortable.\n");
   add_item("carpet",
      "It is a wool carpet made of purple-dyed threads interwoven with "+
      "intricate circles and scrolls in a typical celtic design.\n");
   add_item(({"shelfs","bookshelves","books","documents"}),
      "The office is crammed with ceiling-high shelves on which hundreds "+
      "of official-looking books and documents are placed. You guess "+
      "they are probably full of old deeds, pronouncements, vital "+
      "statistics and any other records the village would keep. They "+
      "look somewhat disorganized and you figure the one who works "+
      "here is the only one who could find anything--job security.\n");
   add_item(({"roof","ceiling","floor"}),
      "The roof of the hall made of high angled rafters covered with "+
      "wood planks, just like the floor.\n");
 
   add_exit("townhall","west");
   reset_room();
}
