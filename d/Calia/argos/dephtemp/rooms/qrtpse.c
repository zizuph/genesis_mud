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
 
#define NUM 2
object *priestess=allocate(NUM);
 
void
make_monster(int i)
{
    if (priestess[i]) return;
    priestess[i]=clone_object(NPC_DIR+"bathpsts");
    priestess[i]->equip_me();
    priestess[i]->move(THIS);
    tell_room(THIS, QCNAME(priestess[i])+" rises out of the pool.\n");
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
      "Whisps of steam rise from a large rectangular pool which has "+
      "been hewn into the floor of this triangular chamber. A long "+
      "hearth runs the length of the northeastern wall, fires heating "+
      "pots to add to the smothering warmth of the room. The chamber "+
      "is void of furnishings, and a doorway leads west back into "+
      "the corridor.\n");
 
   add_item("steam","Whisps rise from the pool while it boils from "+
                    "the pots in the hearth.\n");
   add_item("pool","It is a large pool set into the floor of the "+
                   "chamber, filled with warm clear water. You "+
                   "notice a mosaic set in the pool's bottom.\n");
   add_item(({"mosaic","pool bottom","bottom of pool"}),
              "Made of pieces of colored tile, the mosaic "+
              "on the bottom of the pool are pieced into the shape "+
              "of nymph with long red hair.\n");
   add_item("hearth","It is a long stone hearth set into the "+
            "northeastern wall. Several small fires are lit below "+
            "iron pots which hang inside the hearth.\n");
   add_item("fires","They burn quitely in the pit of the hearth, "+
            "heating the room to an almost uncomfortably warm "+
            "temperature.\n");
   add_item("pots","They hang inside the hearth over the fires, "+
            "steam rising from them with a slighly spiced aroma.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"corr28","west",0);
   reset_room();
}
