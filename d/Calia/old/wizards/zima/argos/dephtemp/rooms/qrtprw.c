/*
**  Temple of Dephonia, Priests' Quarters, practice room
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
object *priest=allocate(NUM);
 
void
make_monster(int i)
{
    if (priest[i]) return;
    priest[i]=clone_object(NPC_DIR+"pracprst");
    priest[i]->equip_me();
    priest[i]->move(THIS);
    tell_room(THIS, QCNAME(priest[i])+" jumps up from a mat.\n");
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
      "You are in a large triangular chamber which serves as a "+
      "training room for the priests of the temple, where they "+
      "learn their military and defense skills. Large mats are "+
      "spread across the floor, and a multitude of wooden practice "+
      "weapons are stored in a cabinet on the wall. You notice a mural "+
      "painted on the southwestern wall of the chamber. The corridor "+
      "is to the east.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("mats","Large mats made of leather stuffed with straw "+
            "lie on the floor, used to soften the falls of those "+
            "learning the martial arts.\n");
   add_item("cabinet","It is a simple wood cabinet where various "+
            "practice weapons are stored.\n");
   add_cmd_item("cabinet",({"open","unlock"}),
                "The cabinet is locked and can not be opened.\n");
   add_item(({"weapons","practice weapons","weapons in cabinet"}),
            "There are an assortment of wooden spears, shields, "+
            "and swords used in the lessons which occur here. "+
            "Though they probably couldn't kill anyone, it would "+
            "probably hurt to be hit upside the head by one of "+
            "the heavy swords.\n");
   add_item("mural","Covering the entire southwestern wall, the "+
            "mural is a painting of a troop of Dephonian priests "+
            "garbed for battle standing in a row, their leader "+
            "facing them with his arms upraised.\n");
 
   add_exit(ROOM_DIR+"corr26",  "east", 0);
   reset_room();
}
