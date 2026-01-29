/*
**  Temple of Dephonia, Ground Level Corridor
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
**
*/
 
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object guard=0;
 
void
reset_room()
{
    if (guard) return;
    guard=clone_object(NPC_DIR+"corguard");
    guard->equip_me();
    guard->move(THIS);
    tell_room(THIS, QCNAME(guard)+" enters the corridor.\n");
}
 
create_room() {
   set_short("Corridor in the Temple of Dephonia");
   set_long(break_string(
      "You continue down the corridor through the temple of black " +
      "marble, an oil lamp in an alcove lighting your way. A banner " +
      "hangs on the wall of the passageway next to the entrance to a " +
      "chamber to the east, while the corridor continues to the " +
      "northwest and southeast through the dark shrine.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("banner", break_string(
      "Made of red silk, the banner is threaded with a circular " +
      "shield covering two crossed spears.\n",70));
 
   add_item("corridor", break_string(
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the northwest and southeast.\n",70));
 
   add_item("lamp", break_string(
      "The lamp is crafted of silver in the form of a raven, " +
      "its wings spread above its head. " +
      "A small flame flickers from the upraised " +
      "beak of the bird, giving a dim light to the corridor.\n",70));
 
   add_item("alcove", break_string(
      "Smoothly carved into the wall of the corridor, this alcove " +
      "has an arched top and serves as a small shelf, upon which " +
      "rests a silver lamp.\n",70));
 
 
   add_exit(ROOM_DIR+"corr11",  "northwest", 0);
   add_exit(ROOM_DIR+"corr17",  "southeast", 0);
   add_exit(ROOM_DIR+"captngrd","east", 0);
   reset_room();
}
