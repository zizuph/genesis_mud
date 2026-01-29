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
      "The echo of your footsteps off the cold dark temple walls " +
      "haunt you as you make your way through the corridor, dimly " +
      "lit by a silver lamp in an alcove. There is an unornamented " +
      "entrance to a chamber to the east, while the corridor " +
      "runs southwest and northeast through the shrine.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("corridor", break_string(
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the southwest and northeast.\n",70));
 
   add_item("lamp", break_string(
      "The lamp is crafted of silver in the form of a raven, " +
      "its wings spread above its head. " +
      "A small flame flickers from the upraised " +
      "beak of the bird, giving a dim light to the corridor.\n",70));
 
   add_item("alcove", break_string(
      "Smoothly carved into the wall of the corridor, this alcove " +
      "has an arched top and serves as a small shelf, upon which " +
      "rests a silver lamp.\n",70));
 
 
   add_exit(ROOM_DIR+"corr15",  "southwest", 0);
   add_exit(ROOM_DIR+"corr17",  "northeast", 0);
   add_exit(ROOM_DIR+"armoury", "east", 0);
   reset_room();
}
