/*
**  Temple of Dephonia, Priests' Quarters
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
#define NUM 3
object *priest=allocate(NUM);
 
void
make_monster(int i)
{
    if (priest[i]) return;
    priest[i]=clone_object(NPC_DIR+"qrtprst");
    priest[i]->equip_me();
    priest[i]->move(THIS);
    tell_room(THIS, QCNAME(priest[i])+" walks in from the corridor.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Priests Quarters in the Temple of Dephonia");
   set_long(
      "This odd-shaped room is one of the chambers for the priests "+
      "of the Order. Beds line the west, northwest and east walls "+
      "set in perfect order, while two large wardrobes sit on "+
      "either side of the doorway to the south. A tapestry hangs "+
      "on the western wall.\n");
 
   add_item("tapestry","Woven of coarse amber wool, the tapestry "+
            "bears the faded image of a warrior dressed in an "+
            "elaborate set of armour, head upraised holding aloft "+
            "a long sword.\n");
 
   add_item(({"room","chamber","walls"}), "The chamber is constructed "+
              "with four walls, one to the east, west and south, "+
              "while the northern wall slants from the southwest "+
              "to the northeast.\n");
 
   add_item(({"doorway","corridor"}), "It is to the south.\n");
 
   add_item(({"bed","beds"}), "They are simple single beds made of "+
              "dark pine wood. They are set in perfect order around "+
              "the perimeter of the room, their heads to the walls.\n");
 
   add_item(({"wardrobe","wardrobes"}), "The wardrobes are tall "+
              "cabinet-like furnishings, one each on either side "+
              "of the doorway to the south. You guess they contain "+
              "the clothes and other items of the priests who sleep "+
              "here.\n");
   add_cmd_item(({"wardrobe","wardrobes"}), ({"open","unlock"}),
              "The wardrobes are locked and can not be opened.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"corr26",  "south", 0);
   reset_room();
}
