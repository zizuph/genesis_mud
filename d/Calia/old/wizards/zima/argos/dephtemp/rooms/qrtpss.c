/*
**  Temple of Dephonia, Priestess' Quarters
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
 
#define NUM 4
object *priestess=allocate(NUM);
 
void
make_monster(int i)
{
    if (priestess[i]) return;
    priestess[i]=clone_object(NPC_DIR+"qrtprsts");
    priestess[i]->equip_me();
    priestess[i]->move(THIS);
    tell_room(THIS, QCNAME(priestess[i])+" walks in from the corridor.\n");
}
 
void
reset_room()
{
   int i;
   for (i=0; i<NUM; i++) make_monster(i);
}
 
create_room() {
   set_short("Priestess Quarters in the Temple of Dephonia");
   set_long(
      "This odd-shaped room is one of the chambers for the priestesses "+
      "of the Order. Beds line the west, southeast and east walls "+
      "set in perfect order, while two large wardrobes sit on "+
      "either side of the doorway to the north. A tapestry hangs "+
      "on the western wall.\n");
 
   add_item("tapestry","It is made of fine silk, and is threaded "+
            "to portray an image of priests and priestesses lounging "+
            "on the banks of a river, enjoying a feast.\n");
 
   add_item(({"room","chamber","walls"}), "The chamber is constructed "+
              "with four walls, one to the east, west and north, "+
              "while the southern wall slants from the southwest "+
              "to the northeast.\n");
 
   add_item(({"doorway","corridor"}), "It is to the north.\n");
 
   add_item(({"bed","beds"}), "They are simple single beds made of "+
              "dark pine wood. They are set in perfect order around "+
              "the perimeter of the room, their heads to the walls.\n");
 
   add_item(({"wardrobe","wardrobes"}), "The wardrobes are tall "+
              "cabinet-like furnishings, one each on either side "+
              "of the doorway to the north. You guess they contain "+
              "the clothes and other items of the priestesses who sleep "+
              "here.\n");
   add_cmd_item(({"wardrobe","wardrobes"}), ({"open","unlock"}),
              "The wardrobes are locked and can not be opened.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"corr28","north",0);
   reset_room();
}
